import pytest

from drunk_snail import Template
from drunk_snail_c import addTemplate, render

from .common import render_lambda



def test_nonexistent_template():
	with pytest.raises(KeyError):
		render_lambda('<!-- (ref)something -->')


def test_buf_overflow():
	assert render_lambda(' ' * 1000)


def test_cyrillic_source():
	assert render_lambda('ляляля') == 'ляляля\n'


def test_cyrillic_name():
	addTemplate('тест_кириллик_нейм', 'lalala')
	assert render('тест_кириллик_нейм', {}) == 'lalala\n'


def test_backslash():
	assert render_lambda('\\') == '\\\n'


def test_quote():
	assert render_lambda('\'') == '\'\n'


def test_brackets():
	assert render_lambda('{<!-- (param)x -->}', {
		'x': 'lalala'
	}) == '{lalala}\n'