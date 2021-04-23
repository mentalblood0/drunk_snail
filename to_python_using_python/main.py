import os
import re

def getTemplateText(name, templates_dir_path, cached_templates):
	if name in cached_templates:
		return cached_templates[name]
	extension = 'xml' if name[0].isupper() else 'txt'
	file_path = os.path.normpath(os.path.join(templates_dir_path, name + '.' + extension))
	return open(file_path, encoding='utf-8').read()

def cacheTemplates(templates_dir_path):
	templates_names = [ ''.join(file_name.split('.')[:-1]) for file_name in os.listdir(templates_dir_path) ]
	templates = { name: getTemplateText(name, templates_dir_path, {}) for name in templates_names }
	return templates

def countIndent(s, character_on_line_index):
	line_start = s.rfind('\n', 0, character_on_line_index)
	if line_start == -1:
		line_start = 0
	return s.count('\t', line_start, character_on_line_index)

def addIndent(s, number_of, dont_indent_lines_started_by=[]):
	indent = number_of * '\t'
	lines = s.split('\n')
	return lines[0] + ('\n' if len(lines) > 1 else '') + '\n'.join([
		(indent + line if not any(line.startswith(substr) for substr in dont_indent_lines_started_by) else line) for line in lines[1:]
	])

def commandsFromLine(line, tags, operators):
	with_tags = r'<!-- *((?:\((?:%s)\))+)(\S*) *-->' % '|'.join(operators)
	result = [{
		'operators': m.groups()[0][1:-1].split(')('),
		'var': m.groups()[1],
		'start': m.start(),
		'end': m.end()
	} for m in list(re.finditer(with_tags, line))]
	return result

def varNameFromCommand(command, tags):
	return command[command.rfind(')')+1:command.rfind(tags['close'])-1]

def parseLine(line, tags, operators):
	result = {
		'source': line,
		'commands': commandsFromLine(line, tags, operators)
	}
	return result

def replaceCommands(parsed_line, way_to_subparams=[], templates_dir_path=None, cached_templates=None):
	result = ''
	last_index = 0
	optional = True
	for c in parsed_line['commands']:
		result += parsed_line['source'][last_index:c['start']]
		current_command_is_optional = False
		for o in c['operators']:
			if o == 'optional':
				current_command_is_optional = True
			elif o == 'param':
				result += f"{{{c['var']}}}"
			elif o == 'ref':
				indent_here = countIndent(result, len(result))
				compiled_subtemplate_text = compileTemplate(
					c['var'],
					root=False,
					way_to_subparams=way_to_subparams,
					templates_dir_path=templates_dir_path,
					cached_templates=cached_templates
				)
				result += addIndent(compiled_subtemplate_text, indent_here, dont_indent_lines_started_by=['#'])
		last_index = c['end']
		if not current_command_is_optional:
			optional = False
	result += parsed_line['source'][last_index:]
	return result, optional

def getUniqueVarsNames(parsed_line):
	return list(set([c['var'] for c in parsed_line['commands']]))

def processLine(line, tags, operators, way_to_subparams=[], templates_dir_path=None, cached_templates=None):
	parsed = parseLine(line, tags, operators)
	unique_vars_names = getUniqueVarsNames(parsed)
	if len(unique_vars_names) == 0:
		return line
	line_with_vars, optional = replaceCommands(parsed, way_to_subparams + [unique_vars_names[0]], templates_dir_path, cached_templates)
	str_way_to_params = 'params' if (len(way_to_subparams) == 0) else way_to_subparams[-1]
	optional_command_conditional_prefix = f'# if \'{unique_vars_names[0]}\' in {str_way_to_params}:\n' if optional else ''
	optional_command_conditional_postfix = '\n# end' if optional else ''
	if len(unique_vars_names) == 1:
		value_by_key = f'{str_way_to_params}[\'{unique_vars_names[0]}\']'
		return f'{optional_command_conditional_prefix}# for {unique_vars_names[0]} in ([None] if ((not {str_way_to_params}) or (not \'{unique_vars_names[0]}\' in {str_way_to_params})) else ({value_by_key} if type({value_by_key}) == list else [{value_by_key}])):\n{line_with_vars}\n# end{optional_command_conditional_postfix}'
	else:
		return '%s# for %s in %s:\n%s\n# endfor%s' % (
			optional_command_conditional_prefix,
			', '.join(unique_vars_names),
			'zip(%s)' % ', '.join(['%s[\'%s\']' % (str_way_to_params, name) for name in unique_vars_names]),
			line_with_vars,
			optional_command_conditional_postfix
		)

def quoteLines(processed_lines):
	result = []
	for line in processed_lines:
		if line[0] == '#':
			result.append(line)
		else:
			result.append(f"result += f'''{line}\\n'''")
	return result

def removeSemicolons(quoted_lines):
	return [(line[1:].strip() if line[0] == '#' else line) for line in quoted_lines]

def fixIndent(lines_without_semicolon, initial_indent=0):
	result = []
	current_indent = initial_indent
	for line in lines_without_semicolon:
		if line[-3:] == 'end':
			current_indent -= 1
			continue
		elif line.endswith(':'):
			result.append('\t' * current_indent + line)
			current_indent += 1
		else:
			result.append('\t' * current_indent + line)
	return result

def joinAdditions(lines_with_fixed_indent):
	prev_line_indent = None
	current_line_indent = None
	for i in range(len(lines_with_fixed_indent)):
		current_line_indent = 0
		for c in lines_with_fixed_indent[i]:
			if c == '\t':
				current_line_indent += 1
			else:
				break
		if current_line_indent == prev_line_indent:
			lines_with_fixed_indent[i-1] = lines_with_fixed_indent[:-3]
			lines_with_fixed_indent[i] = lines_with_fixed_indent[i][current_line_indent + len("result += '''")]
	return lines_with_fixed_indent

def compileTemplate(
	name,
	function_name=None,
	templates_dir_path='templates',
	cached_templates={},
	tags={'open': '<!--', 'close': '-->'},
	operators=['optional', 'param', 'ref'],
	root=True,
	way_to_subparams=[]
):
	template_file_text = getTemplateText(name, templates_dir_path, cached_templates)
	processed_lines = []
	for line in template_file_text.split('\n'):
		processed_lines += processLine(
			line,
			tags,
			operators,
			way_to_subparams=way_to_subparams,
			templates_dir_path=templates_dir_path,
			cached_templates=cached_templates
		).split('\n')
	if root:
		for i in range(len(processed_lines)):
			striped = processed_lines[i].strip()
			if striped[0] == '#':
				processed_lines[i] = striped
		quoted_lines = quoteLines(processed_lines)
		lines_without_semicolon = removeSemicolons(quoted_lines)
		lines_with_fixed_indent = fixIndent(lines_without_semicolon, initial_indent=1)
		lines_with_joined_additions = joinAdditions(lines_with_fixed_indent)
		function_name = function_name or f'fill{name}Template'
		result = [
			f'def {function_name}(params):',
				'\tresult = \'\''
		] + 	lines_with_joined_additions + [
				'\treturn result'
		]
	else:
		result = processed_lines
	return '\n'.join(result)