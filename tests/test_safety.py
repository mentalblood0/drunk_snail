import pytest

from drunk_snail import Template



def test_nonexistent_template():
	with pytest.raises(KeyError):
		Template('test_nonexistent_template', '<!-- (ref)something -->')()


def test_buf_overflow():

	Template(
		'test_buf_overflow_1', 
		' ' * 1000
	)

	assert Template(
		'test_buf_overflow_2', 
		'<!-- (ref)test_buf_overflow_1 -->'
	)()


def test_cyrillic_source():
	assert Template('test_render_cyrillic', 'ляляля')() == 'ляляля\n'


def test_cyrillic_name():
	assert Template('тест_сириллик_нейм', 'lalala')() == 'lalala\n'


def test_backslash():
	assert Template('test_backslash', '\\')() == '\\\n'


def test_quote():
	assert Template('test_quote', '\'')() == '\'\n'


def test_brackets():
	assert Template('test_brackets', '{<!-- (param)x -->}')({
		'x': 'lalala'
	}) == '{lalala}\n'