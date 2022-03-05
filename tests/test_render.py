import pytest

from drunk_snail import Template
from drunk_snail.sources import StringSource, FileSource



def test_basic():
	
	assert Template(
		'test_render_basic', 
		StringSource('<!-- (param)x -->')
	)({
		'x': 'lalala'
	}) == 'lalala'

	assert Template(
		'test_render_basic', 
		StringSource('<!-- (param)x -->\n')
	)({
		'x': 'lalala'
	}) == 'lalala'

	assert Template(
		'test_render_basic', 
		StringSource('lalala')
	)() == 'lalala'



def test_empty_template():
	assert Template('test_render_empty_template', StringSource(''))() == ''


def test_nonexistent_file():
	with pytest.raises(FileNotFoundError):
		Template('test_render_nonexistent_file', FileSource('lalala', watch=False))


def test_nonexistent_template():
	with pytest.raises(KeyError):
		Template('test_nonexistent_template', StringSource('<!-- (ref)something -->')).compiled



def test_list():

	assert Template(
		'test_render_list', 
		StringSource('<!-- (param)some_param -->\n')
	)({
		'some_param': ['1', '2', '3']
	}) == '1\n2\n3'

	assert Template(
		'test_render_list', 
		StringSource('<!-- (param)some_param -->')
	)({
		'some_param': ['1', '2', '3']
	}) == '1\n2\n3'



def test_ref():

	Template(
		'addition', 
		StringSource('Nice to <!-- (param)action --> you')
	)
	t = Template(
		'greeting', 
		StringSource('Hello, <!-- (param)name -->!\n<!-- (ref)addition -->!\n')
	)
	
	assert t({
		'name': 'username',
		'addition': {
			'action': 'eat'
		}
	}) == 'Hello, username!\nNice to eat you!'

	assert Template('greeting')({
		'name': 'username',
		'addition': [{
			'action': 'meet'
		}, {
			'action': 'eat'
		}]
	}) == 'Hello, username!\nNice to meet you!\nNice to eat you!'



def test_buf_overflow():

	Template(
		'test_buf_overflow_1', 
		StringSource(' ' * 100)
	)

	assert Template(
		'test_buf_overflow_2', 
		StringSource('<!-- (ref)test_buf_overflow_1 -->')
	).compiled



def test_consicutive_lines():

	Template(
		'test_consicutive_lines_1',
		StringSource('a')
	)
	Template(
		'test_consicutive_lines_2',
		StringSource('b')
	)
	t = Template(
		'test_consicutive_lines_3',
		StringSource(
			'\t<!-- (optional)(ref)test_consicutive_lines_1 -->\n'
			'\t<!-- (optional)(ref)test_consicutive_lines_2 -->\n'
		)
	)

	assert t({
		'test_consicutive_lines_1': {},
		'test_consicutive_lines_2': {}
	}) == '\ta\n\tb'


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



def test_cyrillic():
	assert Template('test_render_cyrillic', StringSource('ляляля'))() == 'ляляля'


def test_table():

	Template('Row', FileSource('templates/Row.xml'))
	table = Template('Table', FileSource('templates/Table.xml'))

	args = {
		"Row": [
			{"cell": ["1.1", "2.1", "3.1"]},
			{"cell": ["1.2", "2.2", "3.2"]},
			{"cell": ["1.3", "2.3", "3.3"]}
		]
	}

	with open('tests/table_correct_result.xml', encoding='utf8') as f:
		correct_result = f.read()
	assert table(args) == correct_result


def test_other_deep_inject():

	Template('test_other_deep_inject_a', StringSource('a'))
	Template('test_other_deep_inject_b', StringSource('b<!-- (ref)test_other_deep_inject_a -->b'))
	Template('test_other_deep_inject_c', StringSource('c<!-- (ref)test_other_deep_inject_b -->c'))
	d = Template('test_other_deep_inject_d', StringSource('d<!-- (ref)test_other_deep_inject_c -->d'))

	assert d({
		'test_other_deep_inject_b': {
			'test_other_deep_inject_b': {
				'test_other_deep_inject_a': {}
			}
		}
	}) == 'dcbabcd'


def test_endpoint_template():

	t = Template('test_compile_endpoint_template', FileSource('templates/endpoint_template.txt'))

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