import pytest

from drunk_snail import Template
from drunk_snail.sources import StringSource



def test_nonexistent_template():
	with pytest.raises(KeyError):
		Template('test_nonexistent_template', StringSource('<!-- (ref)something -->')).compiled


def test_buf_overflow():

	Template(
		'test_buf_overflow_1', 
		StringSource(' ' * 1000)
	)

	assert Template(
		'test_buf_overflow_2', 
		StringSource('<!-- (ref)test_buf_overflow_1 -->')
	).compiled


def test_cyrillic_source():
	assert Template('test_render_cyrillic', StringSource('ляляля'))() == 'ляляля'


def test_cyrillic_name():
	assert Template('тест_сириллик_нейм', StringSource('lalala'))() == 'lalala'


def test_backslash():
	assert Template('test_backslash', StringSource('\\'))() == '\\'


def test_quote():
	assert Template('test_quote', StringSource('\''))() == '\''


def test_brackets():
	assert Template('test_brackets', StringSource('{<!-- (param)x -->}'))({
		'x': 'lalala'
	}) == '{lalala}'