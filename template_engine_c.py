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

def addTreeNode(tree, way_to_node):
	current_tree_node = tree
	for w in way_to_node:
		if not (w in current_tree_node):
			current_tree_node[w] = {}
		current_tree_node = current_tree_node[w]

def replaceCommands(parsed_line, way_to_subparams=[], params_tree={}):
	addTreeNode(params_tree, way_to_subparams)
	result = ''
	last_index = 0
	optional = True
	is_ref = False
	vars_names = []
	for c in parsed_line['commands']:
		result += parsed_line['source'][last_index:c['start']]
		current_command_is_optional = False
		for o in c['operators']:
			if o == 'optional':
				current_command_is_optional = False
			elif o == 'param':
				result += '%s'
				vars_names.append('*%s' % c['var'])
			elif o == 'ref':
				is_ref = True
				indent_here = countIndent(result, len(result))
				compiled_subtemplate_text = compileTemplate(c['var'], root=False, way_to_subparams=way_to_subparams)
				result += addIndent(compiled_subtemplate_text, indent_here, dont_indent_lines_started_by=['#'])
		last_index = c['end']
		if not current_command_is_optional:
			optional = False
	result += parsed_line['source'][last_index:]
	if len(vars_names) > 0:
		result += ' %% %s' % ', '.join(vars_names)
	return result, optional, is_ref

def getUniqueVarsNames(parsed_line):
	return list(set([c['var'] for c in parsed_line['commands']]))

camel_to_snake_regex = re.compile(r"(?<!^)(?=[A-Z])")

def camelToSnake(s):
	return re.sub(camel_to_snake_regex, "_", s).lower()

def processLine(line, tags, operators, way_to_subparams=[], params_tree={}):
	parsed = parseLine(line, tags, operators)
	unique_vars_names = getUniqueVarsNames(parsed)
	if len(unique_vars_names) == 0:
		return line
	line_with_vars, optional, is_ref = replaceCommands(
		parsed,
		way_to_subparams=way_to_subparams + [unique_vars_names[0]],
		params_tree=params_tree
	)
	str_way_to_params = 'params' if (len(way_to_subparams) == 0) else camelToSnake(way_to_subparams[-1])
	optional_command_conditional_prefix = '# if (*(%s->%s)) {\n' % (
		str_way_to_params,
		unique_vars_names[0]
	) if optional else ''
	optional_command_conditional_postfix = '\n# }' if optional else ''
	if len(unique_vars_names) == 1:
		field_name = camelToSnake(unique_vars_names[0])
		value_by_key = '%s->%s' % (str_way_to_params, field_name)
		iter_var_name = field_name
		iter_var_type = 'struct %s*' % unique_vars_names[0] if is_ref else 'char**'
		iter_var = value_by_key
		return '%s# %s %s = %s;\n# for (; *%s; %s++) {\n%s\n# }%s' % (
			optional_command_conditional_prefix,
			iter_var_type,
			iter_var_name,
			iter_var,
			iter_var_name,
			iter_var_name,
			line_with_vars,
			optional_command_conditional_postfix
		)
	else:
		return '%s# for (%s in %s) {\n%s\n# }%s' % (
			optional_command_conditional_prefix,
			', '.join(unique_vars_names),
			'zip(%s)' % ', '.join(['%s[\'%s\']' % (str_way_to_params, name) for name in unique_vars_names]),
			line_with_vars,
			optional_command_conditional_postfix
		)

def quoteLines(processed_lines):
	result = []
	for line in processed_lines:
		line = line.replace('"', '\\"')
		if line.startswith('#'):
			result.append(line)
		elif '%' in line:
			last_inclusion = line.rfind('%')
			result.append('result_end += sprintf(result_end, "%s\\n", %s);' % (line[:last_inclusion-1], line[last_inclusion-1:].replace(' % ', '')))
		else:
			result.append('result_end += sprintf(result_end, "%s\\n");' % line)
	return result

def removeSemicolons(quoted_lines):
	return [(re.sub(r' *# *(\t*.*)', r'\1', line) if line.startswith('#') else line) for line in quoted_lines]

def fixIndent(lines_without_semicolon, initial_indent=0):
	result = []
	current_indent = initial_indent
	for line in lines_without_semicolon:
		if line.endswith('}'):
			current_indent -= 1
			result.append('\t' * current_indent + line)
		elif line.endswith('{'):
			result.append('\t' * current_indent + line)
			current_indent += 1
		else:
			result.append('\t' * current_indent + line)
	return result

def joinAdditions(lines_with_fixed_indent):
	# return lines_with_fixed_indent
	joined = '\n'.join(lines_with_fixed_indent)
	while True:
		subed = re.sub(r'\n(\t*)(r.*)\"\);\n\1result_end \+= sprintf\(result_end, \"', r'\n\1\2', joined)
		if subed != joined:
			joined = subed
		else:
			break
	return joined.split('\n')

def getStructsDefinitionsFromParamsTree(params_tree, root=True):
	if root:
		params_tree = {'Params': params_tree}
	result_lines = []
	for name, inclusions in params_tree.items():
		if len(inclusions) == 0:
			continue
		result_lines += getStructsDefinitionsFromParamsTree(inclusions, root=False)
		result_lines += [
			f'struct {name} {{', *[
				f'\tstruct {inc_name} *{camelToSnake(inc_name)};' if len(inclusions[inc_name]) > 0
				else f'\tchar **{inc_name.lower()};'
				for inc_name in inclusions
			],
			'};',
			''
		]
	return '\n'.join(result_lines) if root else result_lines

import json

def compileTemplate(
	name,
	function_name=None,
	templates_dir_path='templates',
	cached_templates={},
	tags={'open': '<!--', 'close': '-->'},
	operators=['optional', 'param', 'ref'],
	root=True,
	way_to_subparams=[],
	params_tree={}
):
	template_file_text = getTemplateText(name, templates_dir_path, cached_templates)
	processed_lines = []
	for line in template_file_text.split('\n'):
		processed_lines += processLine(
			line,
			tags,
			operators,
			way_to_subparams=way_to_subparams,
			params_tree=params_tree
		).split('\n')
	if root:
		striped_lines = [(line.strip() if line.strip().startswith('#') else line) for line in processed_lines]
		quoted_lines = quoteLines(striped_lines)
		lines_without_semicolon = removeSemicolons(quoted_lines)
		lines_with_fixed_indent = fixIndent(lines_without_semicolon, initial_indent=1)
		lines_with_joined_additions = joinAdditions(lines_with_fixed_indent)
		function_name = function_name or 'fill%sTemplate' % name
		structs_definitions = getStructsDefinitionsFromParamsTree(params_tree)
		result = [
			'#include <stdio.h>',
			'#include <stdlib.h>\n',
			structs_definitions,
			'char* %s(struct Params *params) {' % function_name,
				# '\tparams = TemplateParameters(params_dict)',
				'\tchar *result = (char*)malloc(sizeof(char) * 100000);',
				'\tchar *result_end = result;'
		] + 	lines_with_joined_additions + [
				'\treturn result;',
				'}'
		]
	else:
		result = processed_lines
	return '\n'.join(result)