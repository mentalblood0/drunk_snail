import pytest

from drunk_snail import Template
from drunk_snail.sources import StringSource



approaches = ['comprehension']


@pytest.mark.parametrize('approach', approaches)
def test_basic(approach: str):
	
	t = Template(
		'test_reload_basic', 
		StringSource('<!-- (param)some_param -->'), 
		approach=approach
	)

	assert t({
		'some_param': 'lalala'
	}) == 'lalala'

	t.reload(source=StringSource('<!-- (param)x -->\n<!-- (param)y -->'))
	assert t({
		'x': 1,
		'y': 2
	}) == '1\n2'


@pytest.mark.parametrize('approach', approaches)
def test_ref(approach: str):

	t1 = Template(
		'test_reload_ref_1', 
		StringSource('<!-- (param)p -->'), 
		approach=approach
	)

	t2 = Template(
		'test_reload_ref_2', 
		StringSource('<!-- (ref)test_reload_ref_1 -->'), 
		approach=approach
	)

	result = t2({
		'test_reload_ref_1': {
			'p': 1
		}
	})
	assert result == '1' or result == '1\n'

	Template(t1.name, StringSource('__<!-- (param)p -->__'), approach=approach)

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
		StringSource('<!-- (param)p -->'), 
		approach=approach
	)

	t2 = Template(
		'test_reload_cascade_2', 
		StringSource('<!-- (ref)test_reload_cascade_1 -->'), 
		approach=approach
	)

	t3 = Template(
		'test_reload_cascade_3', 
		StringSource('<!-- (ref)test_reload_cascade_1 -->\n<!-- (ref)test_reload_cascade_2 -->'), 
		approach=approach
	)

	assert t1.reload(source=StringSource('__<!-- (param)p -->__')) == 1
	assert t2.compiled and (t1.reload(source=StringSource('__<!-- (param)p -->__')) == 2)
	assert t3.compiled and (t1.reload(source=StringSource('__<!-- (param)p -->__')) == 2)