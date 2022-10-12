import pytest

from drunk_snail import Template



def test_basic():

	t = Template('test_reload_basic')

	t.register(
		'<!-- (param)some_param -->'
	)
	assert t({
		'some_param': b'lalala'
	}) == b'lalala\n'

	t.register('<!-- (param)x -->\n<!-- (param)y -->')
	assert t({
		'x': b'1',
		'y': b'2'
	}) == b'1\n2\n'


def test_remove():

	t = Template('test_remove')
	with pytest.raises(KeyError):
		t.text

	t.register('lalala')
	assert t.text == b'lalala'

	t.unregister()
	with pytest.raises(KeyError):
		t.text