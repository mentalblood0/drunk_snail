import json



keywords = [
	'ARG',
	'TEMPLATE_NAME'
]


def compilePrint(approach, fragment_name, expression):
	
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
	
	prefix = f'compile{approach.capitalize()}__{fragment_name}'

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
				f'\tmemcpy(result_end, {prefix}_strings[{strings_copied}], {len(e["s"])}); result_end += {len(e["s"])};'
			)
			strings_copied += 1
		elif e['type'] == 'keyword':
			cpy_definition_list.append(
				f'\tmemcpy(result_end, {e["s"]}_start, {e["s"]}_end - {e["s"]}_start); result_end += {e["s"]}_end - {e["s"]}_start;'
			)
	cpy_definition_list.append('}')
	
	cpy_definition = '\\\n'.join(cpy_definition_list)

	result = f'{strings_definition}\n\n{cpy_definition}'

	return result


expression = "for $ARG$ in ([None] if ((not $TEMPLATE_NAME$) or (not '$ARG$' in $TEMPLATE_NAME$))"\
" else ($TEMPLATE_NAME$['$ARG$'] if type($TEMPLATE_NAME$['$ARG$']) == list else [$TEMPLATE_NAME$['$ARG$']]))"

result = compilePrint('Comprehension', 'for_end', expression)
print(result)