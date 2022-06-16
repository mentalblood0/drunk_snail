from drunk_snail import Template
from drunk_snail.sources import StringSource



def test_basic():
	
	t = Template(
		'test_reload_basic', 
		StringSource('<!-- (param)some_param -->')
	)

	assert t({
		'some_param': 'lalala'
	}) == 'lalala\n'

	t.reload(source=StringSource('<!-- (param)x -->\n<!-- (param)y -->'))
	assert t({
		'x': 1,
		'y': 2
	}) == '1\n2\n'