import pytest

from drunk_snail import Template
from drunk_snail.sources import StringSource
from drunk_snail.syntax import default_keywords



keywords = {
	'open_tag': '(',
	'close_tag': ')',
	'param_operator': '$',
	'ref_operator': '~'
}

approaches = ['comprehension', 'append']


@pytest.mark.parametrize('approach', approaches)
def test_basic(approach: str):
	
	t = Template(
		'test_reload_basic', 
		StringSource('( $some_param )'), 
		keywords,
		approach=approach
	)

	assert t({
		'some_param': 'lalala'
	}) == 'lalala'

	t.reload(source=StringSource('<!-- (param)x -->\n( $y )'))
	assert t({
		'x': 1,
		'y': 2
	}) == '<!-- (param)x -->\n2'

	t = Template('test_reload_basic', keywords=default_keywords)
	assert t({
		'x': 1,
		'y': 2
	}) == '1\n( $y )'


@pytest.mark.parametrize('approach', approaches)
def test_ref(approach: str):

	t1 = Template(
		'test_reload_ref_1', 
		StringSource('( $p )'), 
		keywords,
		approach=approach
	)

	t2 = Template(
		'test_reload_ref_2', 
		StringSource('( ~test_reload_ref_1 )'), 
		keywords,
		approach=approach
	)

	result = t2({
		'test_reload_ref_1': {
			'p': 1
		}
	})
	assert result == '1' or result == '1\n'

	Template(t1.name, StringSource('__( $p )__'), approach=approach)

	result = t2({
		'test_reload_ref_1': {
			'p': 1
		}
	})
	assert result == '__1__' or result == '__1__\n'


@pytest.mark.parametrize('approach', approaches)
def test_cascade(approach: str):

	t1 = Template(
		'test_reload_cascade_1', 
		StringSource('( $p )'), 
		keywords,
		approach=approach
	)

	t2 = Template(
		'test_reload_cascade_2', 
		StringSource('( ~test_reload_cascade_1 )'), 
		keywords,
		approach=approach
	)

	t3 = Template(
		'test_reload_cascade_3', 
		StringSource('( ~test_reload_cascade_1 )\n( ~test_reload_cascade_2 )'), 
		keywords,
		approach=approach
	)

	assert t1.reload(source=StringSource('__( $p )__')) == 1
	assert t2.compiled and (t1.reload(source=StringSource('__( $p )__')) == 2)
	assert t3.compiled and (t1.reload(source=StringSource('__( $p )__')) == 2)