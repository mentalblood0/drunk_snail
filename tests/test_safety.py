import pytest

from drunk_snail_c import addTemplate, render

from .common import render_lambda, param_values



def test_nonexistent_template():
	with pytest.raises(KeyError):
		render_lambda('<!-- (ref)something -->')


def test_buf_overflow():
	assert render_lambda(' ' * 1000)


def test_other_overflow(param_values):

	for name in param_values[:1]:
		addTemplate(f'test_other_deep_inject_{name}', name)

	for i, name in enumerate(param_values[1:]):
		addTemplate(
			f'test_other_deep_inject_{name}',
			f'{name}<!-- (ref)test_other_deep_inject_{param_values[i]} -->{name}'
		)

	print('start')
	result = render(
		f'test_other_deep_inject_{param_values[-1]}',
		{}
	)
	print(f'"{result}"')
	correct = f"{''.join(reversed(param_values))[:-1]}{''.join(param_values)}\n"
	print(f'"{correct}"')
	assert result == correct


def test_name_overflow(value='param'):

	name = 'a' * 200
	assert render_lambda(f'<!-- (param){name} -->', {name: value}) == f'{value}\n'


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