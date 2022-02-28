import re
import json
import argparse



parser = argparse.ArgumentParser(description='Compile prints to optimized form')
parser.add_argument(
	'--file',
	'-f',
	help='Path to file to compile',
	required=True
)
parser.add_argument(
	'--output',
	'-o',
	help='Path to output file',
	required=False
)


includes_types = {
	'keyword': r'ARG|TEMPLATE_NAME|LINE|OTHER_LEFT|OTHER_RIGHT',
	'repetition': r'\w+\*\w+',
	'condition': r'\w+\?[^:]*:[^:]*'
}


def compilePrint(expression, name=None, defined=None):

	parsed = []
	for s in expression.split('$'):
		if s:
			s_type = None
			for t, regexp in includes_types.items():
				if re.match(regexp, s):
					s_type = t
			if (not s_type) and (s in defined):
				s_type = 'call'
			parsed.append({
				's': s,
				'type': s_type
			})
	
	definitions = []

	indent = '\t'
	definitions.append(
		f'char *{name}_strings[{len([True for e in parsed if not e["type"]])}]'\
		f' = {{{json.dumps([e["s"] for e in parsed if not e["type"]], indent=indent)[1:-1]}}};'
	)
	
	args = ['target']
	for w in [e['s'] for e in parsed if e['type'] == 'keyword']:
		if w not in args:
			args.append(w)
			args.append(f'{w}_length')
	
	cpy_definition_list = []
	strings_copied = 0
	counter = f'{name}__i'
	is_counter_defined = False
	for e in parsed:

		if e['type'] == None:
			cpy_definition_list.append(
				f'\tmemcpy(target, {name}_strings[{strings_copied}], {len(e["s"])}); target += {len(e["s"])};'
			)
			strings_copied += 1
		
		elif e['type'] == 'keyword':
			cpy_definition_list.append(
				f'\tmemcpy(target, {e["s"]}, {e["s"]}_length); target += {e["s"]}_length;'
			)
		
		elif e['type'] == 'repetition':

			s, number = e['s'].split('*')

			if not is_counter_defined:
				definitions.insert(0, f'int {counter};')
			
			for a in [s, f'{s}_length', number]:
				if a not in args:
					args.append(a)

			cpy_definition_list += [
				f'\tfor ({counter} = 0; {counter} < {number}; {counter}++) {{',
				f'\t\tmemcpy(target, {s}, {s}_length);',
				f'\t\ttarget += {s}_length;',
				f'\t}}'
			]
		
		elif e['type'] == 'condition':

			condition_object, values = e['s'].split('?')
			value_if_true, value_if_false = values.split(':')

			cpy_definition_list += [
				f'\tif ({condition_object})',
				f'\t\tmemcpy(target, "{value_if_true}", {len(value_if_true)});',
				f'\telse',
				f'\t\tmemcpy(target, "{value_if_false}", {len(value_if_false)});'
			]
		
		elif e['type'] == 'call':

			call_name = e['s']
			call_args = defined[e['s']]

			for a in call_args:
				if a not in args:
					args.append(a)

			cpy_definition_list += [
				f'\t{call_name}({", ".join(call_args)});'
			]

	cpy_definition_list.append('};')
	cpy_definition_list.insert(0, f'#define {name}({", ".join(args)}) {{')
	cpy_definition = '\\\n'.join(cpy_definition_list)
	
	definitions.append(cpy_definition)

	return '\n'.join(definitions), args


definitions_regexp = re.compile(r'((.*) {%[ \n]([^%]*)[ \n]%})')

def replacePrints(s):

	result = s
	defined = {}
	found = re.findall(definitions_regexp, s)
	for line, name, expression in found:

		compiled, args = compilePrint(expression, name=name, defined=defined)
		defined[name] = args

		result = result.replace(line, compiled)
	
	return result


args = parser.parse_args()

with open(args.file, encoding='utf8') as f:
	text = f.read()

result = replacePrints(text)

with open(args.output or 'a.out', 'w', encoding='utf8') as f:
	f.write(result)