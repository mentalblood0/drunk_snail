from drunk_snail import Template
from drunk_snail.sources import StringSource



def test_basic():
	
	t = Template(
		'test_reload_basic', 
		StringSource('<!-- (param)some_param -->')
	)

	assert t({
		'some_param': 'lalala'
	}) == 'lalala'

	t.reload(source=StringSource('<!-- (param)x -->\n<!-- (param)y -->'))
	assert t({
		'x': 1,
		'y': 2
	}) == '1\n2'


def test_ref():

	t1 = Template(
		'test_reload_ref_1', 
		StringSource('<!-- (param)p -->')
	)

	t2 = Template(
		'test_reload_ref_2', 
		StringSource('<!-- (ref)test_reload_ref_1 -->')
	)

	assert t2({
		'test_reload_ref_1': {
			'p': 1
		}
	}) == '1'

	Template(t1.name, StringSource('__<!-- (param)p -->__'))

	assert t2({
		'test_reload_ref_1': {
			'p': 1
		}
	}) == '__1__'


def test_cascade():

	t1 = Template(
		'test_reload_cascade_1', 
		StringSource('<!-- (param)p -->')
	)
	t2 = Template(
		'test_reload_cascade_2', 
		StringSource('<!-- (ref)test_reload_cascade_1 -->')
	)
	t3 = Template(
		'test_reload_cascade_3', 
		StringSource('<!-- (ref)test_reload_cascade_1 -->\n<!-- (ref)test_reload_cascade_2 -->')
	)

	assert t1.reload(source=StringSource('__<!-- (param)p -->__')) == 1
	assert t2.compiled and (t1.reload(source=StringSource('__<!-- (param)p -->__')) == 2)
	assert t3.compiled and (t1.reload(source=StringSource('__<!-- (param)p -->__')) == 2)