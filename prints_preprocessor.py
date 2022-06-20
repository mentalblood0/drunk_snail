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


delimeters = re.compile(r'<|>')

includes_types = {
	'keyword': r'ARG|TEMPLATE_NAME|LINE|OTHER_LEFT|OTHER_RIGHT',
	'repetition': r'\w+\*\w+',
	'condition': r'\w+\?[^:]*:[^:]*',
	'subarray': r'(((\w|\*)+)(\.\w+)*)\[:(\w+)\]((\.\w+)*)(\+|\-)',
	'condition_call': r'\*\((\w+)\?([^:]*):([^:]*)\)'
}
for k in includes_types:
	includes_types[k] = re.compile(includes_types[k])


def parseElement(s, defined):

	p = {
		's': s,
		'type': 'raw'
	}

	for t, regexp in includes_types.items():
		match = re.match(regexp, s)
		if match:
			p['type'] = t
			p['groups'] = match.groups()
			break

	if (p['type'] == 'raw') and (s in defined):
		p['type'] = 'call'

	return p


def compilePrint(expression, name=None, defined=None):

	parsed = []
	for s in re.split(delimeters, expression):
		p = parseElement(s, defined)
		print(f'\t{p["type"]} \'{s}\'')
		parsed.append(p)
	
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
	subarrays_lengths_summing = []
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

			for a in [s, f'{s}_length', number]:
				if a not in args:
					args.append(a)

			cpy_definition_list += [
				f'\tfor (i = 0; i < {number}; i++) {{',
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
		
		elif e['type'] == 'condition_call':

			condition_object = e['groups'][0]

			call_name = {
				True: e['groups'][1],
				False: e['groups'][2]
			}
			call_args = {
				True: defined[call_name[True]]['args'],
				False: defined[call_name[False]]['args']
			}
			call_lengths = {
				True: defined[call_name[True]]['lengths'],
				False: defined[call_name[False]]['lengths']
			}

			for a in call_args[True] + call_args[False]:
				if a not in args:
					args.append(a)

			cpy_definition_list += [
				f'\tif ({condition_object}) {{',
				f'\t\t{call_name[True]}({", ".join(call_args[True])});',
				f'\t}}',
				f'\telse {{',
				f'\t\t{call_name[False]}({", ".join(call_args[False])});',
				f'\t}}'
			]

			lengths_copied += max(call_lengths[True], call_lengths[False])
		
		elif e['type'] == 'subarray':

			m, length, path_to_substring = e['groups'][0], e['groups'][4], e['groups'][5]
			direction = e['groups'][-1]

			if '*' in m:
				m = f'({m})'

			cpy_definition_list += [
				f'\tfor (i = 0; i < {length}; i++) {{'
				if direction == '+'
				else f'\tfor (i = {length}-1; i >= 0; i--) {{',
				f'\t\tmemcpy(*target, {m}[i]{path_to_substring}.start, {m}[i]{path_to_substring}.length); *target += {m}[i]{path_to_substring}.length;',
				f'\t}}'
			]

			subarrays_lengths_summing += [
				f'\tfor (i = 0; i < {length}; i++) {{'
				if direction == '+'
				else f'\tfor (i = {length}-1; i >= 0; i--) {{',
				f'\t\tsubarrays_length += {m}[i]{path_to_substring}.length;',
				f'\t}}'
			]

	subarrays_lengths_summing = [
		f'\tsubarrays_length = 0;'
	] + subarrays_lengths_summing

	lengths_sum = '+'.join([str(n) for n in lengths_copied + [1]])
	cpy_definition_list = subarrays_lengths_summing + [
		f'\twhile ((*target - render_result->result) + ({lengths_sum}) + subarrays_length >= *buffer_size) {{',
		f'\t\t(*buffer_size) *= 2;',
		f'\t\tnew_result = (char*)realloc(render_result->result, sizeof(char) * (*buffer_size));',
		f'\t\t*target = new_result + (*target - render_result->result);',
		f'\t\trender_result->result = new_result;',
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