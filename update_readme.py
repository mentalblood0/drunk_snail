import os
import re
import json
import platform
from drunk_snail import Template
from sharpener_lite.Session import Session



for name in [
	'README.md',
	'TableRenderingResults.md',
	'RenderingResults.md',
	'RenderingResult.md',
	'Row.xml',
	'Table.xml',
	'Example.md',
	'UsageExample.py'
]:
	with open(os.path.join('templates', name)) as f:
		Template(os.path.splitext(name)[0]).register(f.read())


table_arguments = {
	"Row": [
		{"cell": [b"1", b"2"]},
		{"cell": [b"3", b"4"]}
	]
}
table_arguments_strings = {
	"Row": [
		{"cell": ["1", "2"]},
		{"cell": ["3", "4"]}
	]
}
table_arguments_text = json.dumps(
	table_arguments_strings,
	indent='    '
).replace(
	'"1', 'b"1'
).replace(
	'"2', 'b"2'
).replace(
	'"3', 'b"3'
).replace(
	'"4', 'b"4'
).encode('utf8')
usage_example_arguments = {
	'row_template': Template('Row').text,
	'table_template': Template('Table').text,
	'table_arguments': table_arguments_text,
	'table_result': Template('Table')(table_arguments)
}
exec(Template('UsageExample')(
	usage_example_arguments
))

with open(os.path.join('benchmarks', 'benchmark_default.json')) as f:
	benchmarks_config = json.load(f)

table_size = benchmarks_config.values().__iter__().__next__().values().__iter__().__next__()['width']
assert all((
	benchmark['width'] == benchmark['height'] and
	benchmark['width'] == table_size
	for module in benchmarks_config.values()
	for benchmark in module.values()
))

experiments_numbers = [
	benchmark['__n__']
	for module in benchmarks_config.values()
	for benchmark in module.values()
]

benchmarks_result = Session('.', 'benchmark_', benchmarks_config)(None, True).as_dict

output_size = benchmarks_result.values().__iter__().__next__().values().__iter__().__next__()['size']
assert all((
	benchmark['size'] == output_size
	for module in benchmarks_result.values()
	for benchmark_name, benchmark in module.items()
	if benchmark_name == 'table'
))


with open(os.path.join(
	'drunk_snail',
	'drunk_snail_python',
	'modules',
	'drunk_snail_c',
	'src',
	'parse.rl'
)) as f:
	syntax = '\n'.join([
		re.sub(' (?:>|%)action(?:_(?:\S)*)', '', striped_line)
		for line in re.match('(?:.|\n)*(}(.|\n)*}%%)(?:.|\n)*', f.read()).groups()[0].split('\n')
		for striped_line in [line.strip('\t;')]
		if (len(striped_line) > 0) and (striped_line not in  ['}', '}%%'])
	][:-2])


result = Template('README')({
	'git_link': b'https://github.com/MentalBlood/drunk_snail',
	'why': [
		b'Faster',
		b'Easy-readable syntax',
		b'Separation of business logic and data'
	],
	'row_template': Template('Row').text,
	'table_template': Template('Table').text,
	'table_arguments': table_arguments_text,
	'table_result': Template('Table')(table_arguments),
	'UsageExample': usage_example_arguments,
	'syntax': syntax.encode('utf8'),
	'Example': [{
		'code': b'<!-- (ref)AnotherTemplateName -->',
		'description': b'includes template(s) with name "AnotherTemplateName"'
	},{
		'code': b'<!-- (param)some_param_name -->',
		'description': b'includes param value(s)'
	},{
		'code': b'<!-- (optional)(ref)AnotherTemplateName -->',
		'description': b'skips line if no template name is provided'
	},{
		'code': b'<!-- (optional)(param)some_param_name -->',
		'description': b'skips line if no param provided'
	}],
	'os': platform.uname().system.encode(),
	'os_version': platform.uname().version.encode(),
	'cpu': platform.uname().processor.encode(),
	'python_version': platform.python_version().encode(),
	'TableRenderingResults': {
		'size': str(table_size).encode('utf8'),
		'experiments_number': f'{min(experiments_numbers)}-{max(experiments_numbers)}'.encode('utf8'),
		'RenderingResults': [{
			'type': b'Engine',
			'output_type': b'template',
			'RenderingResult': sorted([
				{
					'name': module['table']['name_markdown'].encode('utf8'),
					'time': mean_time.encode('utf8'),
					'templates_by_second': str(int(1000 // float(mean_time))).encode('utf8'),
					'mb_by_second': module['table']['speed'].split(' ')[0].encode('utf8')
				}
				for module_name, module in benchmarks_result.items()
				if module_name != 'other'
				for mean_time in [module['table']['mean_time'].split(' ')[0]]
			], key=lambda d: float(d['mb_by_second']))
		}, {
			'type': b'Other',
			'output_type': b'dict',
			'RenderingResult': sorted([
				{
					'name': benchmark['name_markdown'].encode('utf8'),
					'time': mean_time.encode('utf8'),
					'templates_by_second': str(int(1000 // float(mean_time))).encode('utf8'),
					'mb_by_second': benchmark['speed'].split(' ')[0].encode('utf8')
				}
				for benchmark in benchmarks_result['other'].values()
				for mean_time in [benchmark['mean_time'].split(' ')[0]]
			], key=lambda d: float(d['mb_by_second']))
		}]
	}
})


with open('README.md', 'w') as f:
	f.write(result.decode())