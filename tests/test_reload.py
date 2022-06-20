from drunk_snail import Template



def test_basic():
	
	t = Template('test_reload_basic')

	t.register(
		'<!-- (param)some_param -->'
	)
	assert t({
		'some_param': 'lalala'
	}) == 'lalala\n'

	t.register('<!-- (param)x -->\n<!-- (param)y -->')
	assert t({
		'x': 1,
		'y': 2
	}) == '1\n2\n'