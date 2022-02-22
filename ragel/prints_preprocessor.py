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


keywords = [
	'ARG',
	'TEMPLATE_NAME'
]


def compilePrint(expression, target='result_end', approach=None, fragment_name=None, prefix=None):
	
	splited = expression.split('$')
	splited_annotated = [
		{
			's': s,
			'type': 'keyword' if s in keywords else 'string'
		}
		for s in splited
	]

	keywords_sequence = []
	string_sequence = []
	for s in splited:
		if s in keywords:
			keywords_sequence.append(s)
		else:
			string_sequence.append(s)
	
	prefix = prefix or f'compile{approach.capitalize()}__{fragment_name}'

	strings_definition = \
		f'char *{prefix}_strings[{len(string_sequence)}]'\
		f' = {{{json.dumps(string_sequence, indent=4)[1:-1]}}};';
	
	args = []
	for w in set(keywords_sequence):
		args += [
			w,
			f'{w}_length'
		]
	
	cpy_definition_list = [
		f'#define {prefix}_cpy({", ".join(args)}) {{'
	]
	strings_copied = 0
	for e in splited_annotated:
		if e['type'] == 'string':
			cpy_definition_list.append(
				f'\tmemcpy({target}, {prefix}_strings[{strings_copied}], {len(e["s"])}); {target} += {len(e["s"])};'
			)
			strings_copied += 1
		elif e['type'] == 'keyword':
			cpy_definition_list.append(
				f'\tmemcpy({target}, {e["s"]}_start, {e["s"]}_end - {e["s"]}_start); {target} += {e["s"]}_end - {e["s"]}_start;'
			)
	cpy_definition_list.append('};')
	
	cpy_definition = '\\\n'.join(cpy_definition_list)

	result = f'{strings_definition}\n{cpy_definition}'

	return result


def replacePrints(s):

	result = s
	found = re.findall(r'\n((.*) {%\n*\t*(.*)\n\t*%})', s)
	for line, prefix, expression in found:
		compiled = compilePrint(expression, prefix=prefix)
		result = result.replace(line, compiled)
	
	return result


args = parser.parse_args()

with open(args.file, encoding='utf8') as f:
	text = f.read()

result = replacePrints(text)

with open(args.output or 'a.out', 'w', encoding='utf8') as f:
	f.write(result)