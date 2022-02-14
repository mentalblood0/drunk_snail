import os
import pytest
from time import sleep

from drunk_snail import Template
from drunk_snail.syntax import default_keywords
from drunk_snail.sources import StringSource, FileSource



keywords = {
	'open_tag': '(',
	'close_tag': ')',
	'param_operator': '$',
	'ref_operator': '~'
}


def test_basic():
	
	t = Template(
		'test_render_basic', 
		StringSource('( $x )'), 
		keywords
	)
	print(t.compiled)
	
	assert t({
		'x': 'lalala'
	}) == 'lalala'

	assert Template(
		'test_render_basic', 
		StringSource('( $x )\n')
	)({
		'x': 'lalala'
	}) == 'lalala\n'

	assert Template(
		'test_render_basic', 
		StringSource('lalala')
	)({}) == 'lalala'


def test_empty_template():
	assert Template('test_render_empty_template', StringSource(''))() == ''


def test_nonexistent_file():
	with pytest.raises(FileNotFoundError):
		Template('test_render_nonexistent_file', FileSource('lalala', watch=False))


def test_list():

	assert Template(
		'test_render_list', 
		StringSource('( $some_param )\n'), 
		keywords
	)({
		'some_param': ['1', '2', '3']
	}) == '1\n2\n3\n'

	assert Template(
		'test_render_list', 
		StringSource('( $some_param )'), 
		keywords
	)({
		'some_param': ['1', '2', '3']
	}) == '1\n2\n3'


def test_ref():

	Template(
		'addition', 
		StringSource('Nice to ( $action ) you'), 
		keywords
	)

	Template(
		'greeting', 
		StringSource('Hello, ( $name )!\n( ~addition )!\n'), 
		keywords
	)
	
	assert Template('greeting')({
		'name': 'username',
		'addition': {
			'action': 'eat'
		}
	}) == 'Hello, username!\nNice to eat you!\n'

	print(Template('greeting').compiled)

	result = Template('greeting')({
		'name': 'username',
		'addition': [{
			'action': 'meet'
		}, {
			'action': 'eat'
		}]
	})
	print(result)
	assert result == 'Hello, username!\nNice to meet you!\nNice to eat you!\n'


def test_buf_overflow():

	t1 = Template(
		'test_buf_overflow_1', 
		StringSource(' ' * 1000),
		keywords
	)

	t2 = Template(
		'test_buf_overflow_2', 
		StringSource('( ~test_buf_overflow_1 )'),
		keywords
	)

	assert t2.compiled


def test_consicutive_lines():

	t1 = Template(
		'test_consicutive_lines_1',
		StringSource('a')
	)

	t2 = Template(
		'test_consicutive_lines_2',
		StringSource('b')
	)

	t3 = Template(
		'test_consicutive_lines_3',
		StringSource('''
\t<!-- (optional)(ref)test_consicutive_lines_1 -->
\t<!-- (optional)(ref)test_consicutive_lines_2 -->
''')
	)

	result = t3({
		'test_consicutive_lines_1': {},
		'test_consicutive_lines_2': {}
	})
	assert result == '''
\ta
\tb
'''


def test_optional_param():
	assert Template(
		'test_optional_param',
		StringSource('<!-- (optional)(param)a -->')
	)() == ''


def test_optional_ref():

	Template(
		'test_optional_ref_1',
		StringSource('lalala')
	)
	t = Template(
		'test_optional_ref_2',
		StringSource('<!-- (optional)(ref)test_optional_ref_1 -->')
	)
	
	assert t() == ''
	assert t({
		'test_optional_ref_1': [None]
	}) == 'lalala'


def test_shift():

	for letter in ['a', 'b', 'c', 'd']:
		Template(letter, FileSource(f'templates/{letter.upper()}.xml'))
	
	result = Template('a')({'B': {'C': [{}, {}]}})

	valid_tabs_number = 60
	assert result.count('\t') == valid_tabs_number


def test_cyrillic():

	t = Template('test_render_cyrillic', StringSource('ляляля'))

	assert t() == 'ляляля'


def test_table():

	table = Template('Table', FileSource('templates/Table.xml'))
	row = Template('Row', FileSource('templates/Row.xml'))

	# print(table.compiled)
	# assert False
	
	args = {
		"Row": [
			{"cell": ["1.1", "2.1", "3.1"]},
			{"cell": ["1.2", "2.2", "3.2"]},
			{"cell": ["1.3", "2.3", "3.3"]}
		]
	}

	result = table(args)

	with open('tests/table_correct_result.xml', encoding='utf8') as f:
		correct_result = f.read()
	assert result == correct_result


def test_endpoint_template():

	t = Template('test_compile_endpoint_template', FileSource('templates/endpoint_template.txt', watch=False))
	
	assert t({
		'route_to': 'route_to',
		'methods': 'methods',
		'handler_name': 'handler_name',
		'handler_args': ', '.join(['a', 'b'])
	}) == """from ..common import *



@route(
	None, 
	'route_to', 
	methods=methods
)
def handler_name(
	a, b
):
	return Response(status=200)"""