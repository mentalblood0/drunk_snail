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

def replaceCommands(parsed_line, way_to_subparams=[]):
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
				result += '{%s}' % c['var']
			elif o == 'ref':
				indent_here = countIndent(result, len(result))
				compiled_subtemplate_text = compileTemplate(c['var'], root=False, way_to_subparams=way_to_subparams)
				result += addIndent(compiled_subtemplate_text, indent_here, dont_indent_lines_started_by=['#'])
		last_index = c['end']
		if not current_command_is_optional:
			optional = False
	result += parsed_line['source'][last_index:]
	return result, optional

def getUniqueVarsNames(parsed_line):
	return list(set([c['var'] for c in parsed_line['commands']]))

def processLine(line, tags, operators, way_to_subparams=[]):
	parsed = parseLine(line, tags, operators)
	unique_vars_names = getUniqueVarsNames(parsed)
	if len(unique_vars_names) == 0:
		return line
	line_with_vars, optional = replaceCommands(parsed, way_to_subparams + [unique_vars_names[0]])
	str_way_to_params = 'params' if (len(way_to_subparams) == 0) else way_to_subparams[-1]
	optional_command_conditional_prefix = '# if \'%s\' in %s:\n' % (
		unique_vars_names[0],
		str_way_to_params
	) if optional else ''
	optional_command_conditional_postfix = '\n# endif' if optional else ''
	if len(unique_vars_names) == 1:
		value_by_key = '%s[\'%s\']' % (str_way_to_params, unique_vars_names[0])
		return '%s# for %s in ([None] if ((not %s) or (not \'%s\' in %s)) else (%s if type(%s) == list else [%s])):\n%s\n# endfor%s' % (
			optional_command_conditional_prefix,
			unique_vars_names[0],
			str_way_to_params,
			unique_vars_names[0],
			str_way_to_params,
			value_by_key,
			value_by_key,
			value_by_key,
			line_with_vars,
			optional_command_conditional_postfix
		)
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
		if line.startswith('#'):
			result.append(line)
		else:
			result.append("result += f'''%s\\n'''" % line)
	return result

def removeSemicolons(quoted_lines):
	return [(line[len('#'):].strip() if line.startswith('#') else line) for line in quoted_lines]

def fixIndent(lines_without_semicolon, initial_indent=0):
	result = []
	current_indent = initial_indent
	for line in lines_without_semicolon:
		if line.endswith('end'):
			current_indent -= 1
			continue
		elif line.endswith(':'):
			result.append('\t' * current_indent + line)
			current_indent += 1
		else:
			result.append('\t' * current_indent + line)
	return result

def joinAdditions(lines_with_fixed_indent):
	joined = '\n'.join(lines_with_fixed_indent)
	while True:
		subed = re.sub(r"\n(\t*)(r.*)'''\n\1result \+= f'''", r'\n\1\2', joined)
		if subed != joined:
			joined = subed
		else:
			break
	return joined.split('\n')

expressions_to_compile_template = [(
		r'^(?!.*<!-- *\(param|ref\)\S* *-->)(.*)',
		r"result += '''\1'''"
	),(
		r"'''\nresult \+= '''",
		r'\\n'
	),(
		r'(\t*.*)<!-- *\(param\)(\S*) *-->(.*)',
		r"for \2 in ([None] if ((not Header) or (not '\2' in Header)) else (Header['\2'] if type(Header['\2']) == list else [Header['\2']])):\nresult += '''\1{\2}\3'''\nend"
	),(
		r'(\t*.*)<!-- *\(ref\)(\S*) *-->(.*)',
		lambda m: m.group(1) + compileTemplate(m.group(2)) + m.group(3)
	)
]

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
	result = template_file_text
	for exp in expressions_to_compile_template:
		result = re.sub(exp[0], exp[1], result, flags=re.MULTILINE)
		# print(result)
		# print('------------------------------------------')
	result = '\n'.join(fixIndent(result.split('\n')))
	return result