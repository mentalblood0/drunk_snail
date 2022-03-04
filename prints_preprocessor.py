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
	'condition': r'\w+\?[^:]*:[^:]*',
	'subarray': r'((\w+)(\.\w+)*)\[:(\w+)\]((\.\w+)*)(\+|\-)'
}
for k in includes_types:
	includes_types[k] = re.compile(includes_types[k])


def compilePrint(expression, name=None, defined=None):

	parsed = []
	for i, s in enumerate(expression.split('$')):
		
		element = {
			's': s,
			'type': 'raw'
		}

		if i % 2:
	
			for t, regexp in includes_types.items():
				match = re.match(regexp, s)
				if match:
					element['type'] = t
					element['groups'] = match.groups()
					break
		
			if (element['type'] == 'raw') and (s in defined):
				element['type'] = 'call'
		
			print(f'\t{element["type"]} \'{s}\'')
	
		parsed.append(element)
	
	definitions = []
	raw_strings = [e["s"] for e in parsed if e["type"] == 'raw']
	
	args = ['target']
	for w in [e['s'] for e in parsed if e['type'] == 'keyword']:
		if w not in args:
			args.append(w)
			args.append(f'{w}_length')
	
	cpy_definition_list = []
	lengths_copied = []
	strings_copied = 0
	counter = f'{name}__i'
	is_counter_defined = False
	for e in parsed:

		if e['type'] == 'raw':
			cpy_definition_list.append(
				f'\tmemcpy(*target, {json.dumps(raw_strings[strings_copied])}, {len(e["s"])}); *target += {len(e["s"])};'
			)
			strings_copied += 1
			lengths_copied.append(len(e['s']))
		
		elif e['type'] == 'keyword':
			cpy_definition_list.append(
				f'\tmemcpy(*target, {e["s"]}, {e["s"]}_length); *target += {e["s"]}_length;'
			)
			lengths_copied.append(f'{e["s"]}_length')
		
		elif e['type'] == 'repetition':

			s, number = e['s'].split('*')

			if not is_counter_defined:
				definitions.insert(0, f'int {counter};')
				is_counter_defined = True
			
			for a in [s, f'{s}_length', number]:
				if a not in args:
					args.append(a)

			cpy_definition_list += [
				f'\tfor ({counter} = 0; {counter} < {number}; {counter}++) {{',
				f'\t\tmemcpy(*target, {s}, {s}_length);',
				f'\t\t*target += {s}_length;',
				f'\t}}'
			]
			lengths_copied.append(f'{s}_length')
		
		elif e['type'] == 'condition':

			condition_object, values = e['s'].split('?')
			value_if_true, value_if_false = values.split(':')

			cpy_definition_list += [
				f'\tif ({condition_object}) {{',
				f'\t\tmemcpy(*target, "{value_if_true}", {len(value_if_true)}); *target += {len(value_if_true)};',
				f'\t}}',
				f'\telse {{',
				f'\t\tmemcpy(*target, "{value_if_false}", {len(value_if_false)}); *target += {len(value_if_false)};',
				f'\t}}'
			]
			lengths_copied.append(max(len(value_if_true), len(value_if_false)))
		
		elif e['type'] == 'call':

			call_name = e['s']
			call_args = defined[e['s']]['args']
			call_lengths = defined[e['s']]['lengths']

			for a in call_args:
				if a not in args:
					args.append(a)

			cpy_definition_list += [
				f'\t{call_name}({", ".join(call_args)});'
			]
			lengths_copied += call_lengths
		
		elif e['type'] == 'subarray':

			m, length, path_to_substring = e['groups'][0], e['groups'][3], e['groups'][4]
			m = e['groups'][0]
			length = e['groups'][3]
			path_to_substring = e['groups'][4]
			direction = e['groups'][-1]

			if not is_counter_defined:
				definitions.insert(0, f'int {counter};')
				is_counter_defined = True

			cpy_definition_list += [
				f'\tfor ({counter} = 0; {counter} < {length}; {counter}++) {{'
				if direction == '+'
				else f'\tfor ({counter} = {length}-1; {counter} >= 0; {counter}--) {{',
				f'\t\tmemcpy(*target, {m}[{counter}]{path_to_substring}.start, {m}[{counter}]{path_to_substring}.length); *target += {m}[{counter}]{path_to_substring}.length;',
				f'\t}}'
			]

	lengths_sum = '+'.join([str(n) for n in lengths_copied + [1]])
	cpy_definition_list = [
		f'\twhile ((*target - compilation_result->result) + ({lengths_sum}) >= *buffer_size) {{',
		f'\t\t(*buffer_size) *= 2;',
		f'\t\tnew_result = (char*)realloc(compilation_result->result, sizeof(char) * (*buffer_size));',
		f'\t\t*target = new_result + (*target - compilation_result->result);',
		f'\t\tcompilation_result->result = new_result;',
		f'\t}}'
	] + cpy_definition_list

	cpy_definition_list.append('};')
	cpy_definition_list.insert(0, f'#define {name}({", ".join(args)}) {{')
	cpy_definition = '\\\n'.join(cpy_definition_list)
	
	definitions.append(cpy_definition)

	return '\n'.join(definitions), args, lengths_copied


definitions_regexp = re.compile(r'((.*) {%[ \n]([^%]*)[ \n]%})')

def replacePrints(s):

	result = s
	defined = {}
	found = re.findall(definitions_regexp, s)
	for line, name, expression in found:
	
		print(name)

		compiled, args, lengths = compilePrint(expression, name=name, defined=defined)
		defined[name] = {
			'args': args,
			'lengths': lengths
		}

		result = result.replace(line, compiled)
	
	return result


args = parser.parse_args()

with open(args.file, encoding='utf8') as f:
	text = f.read()

result = replacePrints(text)

with open(args.output or 'a.out', 'w', encoding='utf8') as f:
	f.write(result)