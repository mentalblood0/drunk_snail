import drunk_snail
from drunk_snail.sources import StringSource
from drunk_snail import Template, default_keywords



keywords = {
	'open_tag': '(',
	'close_tag': ')',
	'param_operator': '$',
	'ref_operator': '~'
}


def test_basic():
	
	t = Template(
		'test_reload_basic', 
		StringSource('( $some_param )'), 
		keywords
	)
	print(t.compiled)

	assert t({
		'some_param': 'lalala'
	}) == 'lalala'

	# assert False

	t.reload(source=StringSource('<!-- (param)x -->\n( $y )'))
	print(t.compiled)
	assert t({
		'x': 1,
		'y': 2
	}) == '<!-- (param)x -->\n2'

	t = Template('test_reload_basic', keywords=default_keywords)
	print(t.compiled)
	assert t({
		'x': 1,
		'y': 2
	}) == '1\n( $y )'


def test_ref():

	t1 = Template(
		'test_reload_ref_1', 
		StringSource('( $p )'), 
		keywords
	)

	t2 = Template(
		'test_reload_ref_2', 
		StringSource('( ~test_reload_ref_1 )'), 
		keywords
	)

	assert t2({
		'test_reload_ref_1': {
			'p': 1
		}
	}) == '1\n'

	Template(t1.name, StringSource('__( $p )__'))

	assert t2({
		'test_reload_ref_1': {
			'p': 1
		}
	}) == '__1__\n'

def test_cascade():

	t1 = Template(
		'test_reload_cascade_1', 
		StringSource('( $p )'), 
		keywords
	)

	t2 = Template(
		'test_reload_cascade_2', 
		StringSource('( ~test_reload_cascade_1 )'), 
		keywords
	)

	t3 = Template(
		'test_reload_cascade_3', 
		StringSource('( ~test_reload_cascade_1 )\n( ~test_reload_cascade_2 )'), 
		keywords
	)

	assert t1.reload(source=StringSource('__( $p )__')) == 1
	assert t2.compiled and (t1.reload(source=StringSource('__( $p )__')) == 2)
	assert t3.compiled and (t1.reload(source=StringSource('__( $p )__')) == 3)