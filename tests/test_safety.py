import pytest

from drunk_snail_python import addTemplate, removeTemplate, render

from .common import render_lambda, param_values



def test_nonexistent_template():
	with pytest.raises(KeyError):
		render('name', {})


def test_nonexistent_param():
	assert render_lambda('lalala<!-- (param)p -->lololo', {}) == 'lalalalololo\n'


def test_nonexistent_ref():
	with pytest.raises(KeyError):
		render_lambda('<!-- (ref)something -->')


def test_nonexistent_ref_deep():

	addTemplate('test_nonexistent_ref_1', '<!-- (ref)test_nonexistent_ref_2 -->')
	addTemplate('test_nonexistent_ref_2', '<!-- (ref)no -->')
	with pytest.raises(KeyError):
		render('test_nonexistent_ref_1', {})


def test_buf_overflow():
	assert render_lambda(' ' * 1024)


def test_other_overflow(param_values):

	for name in param_values[:1]:
		addTemplate(f'test_other_deep_inject_{name}', name)

	for i, name in enumerate(param_values[1:]):
		addTemplate(
			f'test_other_deep_inject_{name}',
			f'{name}<!-- (ref)test_other_deep_inject_{param_values[i]} -->{name}'
		)

	result = render(
		f'test_other_deep_inject_{param_values[-1]}',
		{}
	)
	correct = f"{''.join(reversed(param_values))[:-1]}{''.join(param_values)}\n"
	assert result == correct


def test_name_overflow(value='param'):
	name = 'a' * 512
	assert render_lambda(f'<!-- (param){name} -->', {name: value}) == f'{value}\n'


def test_value_overflow():
	value = 'a' * 512
	assert render_lambda(f'<!-- (param)name -->', {'name': value}) == f'{value}\n'


def test_stack_overflow(param_values):

	for name in param_values[:1]:
		addTemplate(f'o{name}', '')

	for i, name in enumerate(param_values[1:]):
		addTemplate(
			f'o{name}',
			f'<!-- (ref)o{param_values[i]} -->'
		)

	assert render(f'o{param_values[-1]}', {}) == ''


def test_memory_leak():

	text = ' ' * 1024 * 1024 # 1MB

	for i in range(1024 * 32):
		addTemplate('big', text)
		removeTemplate('big')


def test_cyrillic_source():
	assert render_lambda('ляляля') == 'ляляля\n'


def test_cyrillic_name():
	addTemplate('ляляля', 'lalala')
	assert render('ляляля', {}) == 'lalala\n'


def test_nonstring():
	for template, params in (
		('<!-- (param)x -->',                  {'x': 1}),
		('<!-- (param)x -->',                  {'x': [1]}),
		('<!-- (param)x --><!-- (param)y -->', {'x': '1', 'y': 1})
	):
		with pytest.raises(Exception):
			render_lambda(template, params)