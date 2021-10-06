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
		'test_render', 
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

	t = Template('test_render', keywords=default_keywords)
	print(t.compiled)
	assert t({
		'x': 1,
		'y': 2
	}) == '1\n( $y )'