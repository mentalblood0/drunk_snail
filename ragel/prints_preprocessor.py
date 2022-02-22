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
	'keyword': r'ARG|TEMPLATE_NAME|LINE',
	'repetition': r'(\w|_)+(\*(\w|_)+)+'
}


def compilePrint(expression, name=None):
	
	splited = [
		s
		for s in expression.split('$')
		if s
	]

	parsed = []
	for s in splited:
		s_type = None
		for t, regexp in includes_types.items():
			if re.match(regexp, s):
				s_type = t
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
	
	args = ['target'] + sum([
		[
			w,
			f'{w}_length'
		]
		for w in set([e['s'] for e in parsed if e['type'] == 'keyword'])
	], start=[])
	
	cpy_definition_list = [
		f'#define {name}({", ".join(args)}) {{'
	]
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
				f'\tmemcpy(target, {e["s"]}_start, {e["s"]}_end - {e["s"]}_start); target += {e["s"]}_end - {e["s"]}_start;'
			)
		
		elif e['type'] == 'repetition':

			s, number = e['s'].split('*')

			if not is_counter_defined:
				definitions.insert(0, f'int {counter};')

			cpy_definition_list += [
				f'\tfor ({counter} = 0; counter < {number}; {counter}++) {{',
				f'\t\tmemcpy(target, {s}_start, {s}_end - {s}_start);',
				f'\t\ttarget += {s}_end - {s}_start;',
				f'\t}}'
			]

	cpy_definition_list.append('};')
	cpy_definition = '\\\n'.join(cpy_definition_list)
	
	definitions.append(cpy_definition)

	return '\n'.join(definitions)


def replacePrints(s):

	result = s
	found = re.findall(r'((.*) {%[ \n]([^%]*)[ \n]%})', s)
	for line, name, expression in found:
		compiled = compilePrint(expression, name=name)
		result = result.replace(line, compiled)
	
	return result


args = parser.parse_args()

with open(args.file, encoding='utf8') as f:
	text = f.read()

result = replacePrints(text)

with open(args.output or 'a.out', 'w', encoding='utf8') as f:
	f.write(result)