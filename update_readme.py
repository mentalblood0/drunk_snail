import os
import re
import json
from drunk_snail import Template
from sharpener_lite.Session import Session



for name in [
	'README.md',
	'TableRenderingResults.md',
	'RenderingResults.md',
	'RenderingResult.md',
	'Row.xml',
	'Table.xml',
	'Example.md'
]:
	with open(os.path.join('templates', name)) as f:
		Template(os.path.splitext(name)[0]).register(f.read())


table_arguments = {
	"Row": [
		{"cell": ["1", "2"]},
		{"cell": ["3", "4"]}
	]
}

with open(os.path.join('benchmarks', 'benchmark_default.json')) as f:
	benchmarks_config = json.load(f)

table_size = benchmarks_config.values().__iter__().__next__().values().__iter__().__next__()['width']
for module in benchmarks_config.values():
	for benchmark in module.values():
		assert benchmark['width'] == benchmark['height']
		assert benchmark['width'] == table_size

experiments_numbers = [
	benchmark['__n__']
	for module in benchmarks_config.values()
	for benchmark in module.values()
]

benchmarks_result = Session('.', 'benchmark_', benchmarks_config)(None).as_dict


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
		for striped_line in [line.strip('    ;')]
		if (len(striped_line) > 0) and (striped_line not in  ['}', '}%%'])
	][:-2])


result = Template('README')({
	'git_link': 'https://github.com/MentalBlood/drunk_snail',
	'why': [
		'Faster',
		'Easy-readable syntax',
		'Separation of business logic and data'
	],
	'row_template': Template('Row').text,
	'table_template': Template('Table').text,
	'table_arguments': json.dumps(table_arguments, indent='    '),
	'table_result': Template('Table')(table_arguments),
	'syntax': syntax,
	'Example': [{
		'code': '<!-- (ref)AnotherTemplateName -->',
		'description': 'includes template(s) with name "AnotherTemplateName"'
	},{
		'code': '<!-- (param)some_param_name -->',
		'description': 'includes param value(s)'
	},{
		'code': '<!-- (optional)(ref)AnotherTemplateName -->',
		'description': 'skips line if no template name is provided'
	},{
		'code': '<!-- (optional)(param)some_param_name -->',
		'description': 'skips line if no param provided'
	},{
		'code': '<!-- (strict)(ref)AnotherTemplateName -->',
		'description': 'corresponding object must be list[dict]'
	},{
		'code': '<!-- (strict)(param)some_param_name -->',
		'description': 'corresponding object must be list[string]'
	}],
	'TableRenderingResults': {
		'size': str(table_size),
		'experiments_number': f'{min(experiments_numbers)}-{max(experiments_numbers)}',
		'RenderingResults': [{
			'type': 'Engine',
			'output_type': 'template',
			'RenderingResult': sorted([
				{
					'name': module['table']['name_markdown'],
					'time': mean_time,
					'templates_by_second': str(int(1000 // float(mean_time))),
					'mb_by_second': module['table']['speed'].split(' ')[0]
				}
				for module_name, module in benchmarks_result.items()
				if module_name != 'other'
				for mean_time in [module['table']['mean_time'].split(' ')[0]]
			], key=lambda d: float(d['mb_by_second']))
		}, {
			'type': 'Other',
			'output_type': 'dict',
			'RenderingResult': sorted([
				{
					'name': benchmark['name_markdown'],
					'time': mean_time,
					'templates_by_second': str(int(1000 // float(mean_time))),
					'mb_by_second': benchmark['speed'].split(' ')[0]
				}
				for benchmark in benchmarks_result['other'].values()
				for mean_time in [benchmark['mean_time'].split(' ')[0]]
			], key=lambda d: float(d['mb_by_second']))
		}]
	}
})


with open('README.md', 'w') as f:
	f.write(result)