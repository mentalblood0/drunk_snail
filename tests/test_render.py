import pytest

from drunk_snail import Template



def test_basic():
	
	assert Template(
		'test_render_basic', 
		'<!-- (param)x -->'
	)({
		'x': 'lalala'
	}) == 'lalala\n'

	assert Template(
		'test_render_basic', 
		'<!-- (param)x -->\n'
	)({
		'x': 'lalala'
	}) == 'lalala\n'

	assert Template(
		'test_render_basic', 
		'lalala'
	)() == 'lalala\n'


def test_empty_template():
	assert Template('test_render_empty_template', '')() == ''


def test_list():

	assert Template(
		'test_render_list', 
		'<!-- (param)some_param -->\n'
	)({
		'some_param': ['1', '2', '3']
	}) == '1\n2\n3\n'

	assert Template(
		'test_render_list', 
		'<!-- (param)some_param -->'
	)({
		'some_param': ['1', '2', '3']
	}) == '1\n2\n3\n'


def test_ref():

	Template(
		'addition', 
		'Nice to <!-- (param)action --> you'
	)
	t = Template(
		'greeting', 
		'Hello, <!-- (param)name -->!\n<!-- (ref)addition -->!\n'
	)
	
	assert t({
		'name': 'username',
		'addition': {
			'action': 'eat'
		}
	}) == 'Hello, username!\nNice to eat you!\n'

	assert Template('greeting')({
		'name': 'username',
		'addition': [{
			'action': 'meet'
		}, {
			'action': 'eat'
		}]
	}) == 'Hello, username!\nNice to meet you!\nNice to eat you!\n'


def test_consicutive_lines():

	Template(
		'test_consicutive_lines_1',
		'a'
	)
	Template(
		'test_consicutive_lines_2',
		'b'
	)
	t = Template(
		'test_consicutive_lines_3',
		'\t<!-- (optional)(ref)test_consicutive_lines_1 -->\n'
		'\t<!-- (optional)(ref)test_consicutive_lines_2 -->\n'
	)

	assert t({
		'test_consicutive_lines_1': {},
		'test_consicutive_lines_2': {}
	}) == '\ta\n\tb\n'


def test_optional_param():
	assert Template(
		'test_optional_param',
		'<!-- (optional)(param)a -->'
	)() == ''


def test_optional_ref():

	Template(
		'test_optional_ref_1',
		'lalala'
	)
	t = Template(
		'test_optional_ref_2',
		'<!-- (optional)(ref)test_optional_ref_1 -->'
	)
	
	assert t() == ''
	
	assert t({
		'test_optional_ref_1': [None]
	}) == 'lalala\n'


def test_table():

	Template('Row',
		'<tr>\n'
		'	<td><!-- (strict)(param)cell --></td>\n'
		'</tr>\n'
	)
	table = Template('Table',
		'<table>\n'
		'	<!-- (strict)(ref)Row -->\n'
		'</table>\n'
	)

	args = {
		"Row": [
			{"cell": ["1.1", "2.1", "3.1"]},
			{"cell": ["1.2", "2.2", "3.2"]},
			{"cell": ["1.3", "2.3", "3.3"]}
		]
	}

	assert table(args) == (
		'<table>\n'
		'	<tr>\n'
		'		<td>1.1</td>\n'
		'		<td>2.1</td>\n'
		'		<td>3.1</td>\n'
		'	</tr>\n'
		'	<tr>\n'
		'		<td>1.2</td>\n'
		'		<td>2.2</td>\n'
		'		<td>3.2</td>\n'
		'	</tr>\n'
		'	<tr>\n'
		'		<td>1.3</td>\n'
		'		<td>2.3</td>\n'
		'		<td>3.3</td>\n'
		'	</tr>\n'
		'</table>\n'
	)


def test_other_deep_inject():

	Template('test_other_deep_inject_a', 'a')
	Template('test_other_deep_inject_b', 'b<!-- (ref)test_other_deep_inject_a -->b')
	Template('test_other_deep_inject_c', 'c<!-- (ref)test_other_deep_inject_b -->c')
	d = Template('test_other_deep_inject_d', 'd<!-- (ref)test_other_deep_inject_c -->d')

	assert d({
		'test_other_deep_inject_b': {
			'test_other_deep_inject_b': {
				'test_other_deep_inject_a': {}
			}
		}
	}) == 'dcbabcd\n'


def test_endpoint_template():

	t = Template('test_compile_endpoint_template', 
		'from ..common import *\n'
		'\n'
		'\n'
		'\n'
		'@route(\n'
		'	None, \n'
		"	'<!-- (param)route_to -->', \n"
		'	methods=<!-- (param)methods -->\n'
		')\n'
		'def <!-- (param)handler_name -->(\n'
		'	<!-- (param)handler_args -->\n'
		'):\n'
		'	return Response(status=200)'
	)

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
	return Response(status=200)
"""