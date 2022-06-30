import pytest

from drunk_snail_python import render, addTemplate

from .common import render_lambda, param_values



@pytest.fixture
def param_name():
	return 'x'


@pytest.fixture
def param_value():
	return 'lalala'


@pytest.fixture
def params_one(param_name, param_value):
	return {param_name: param_value}


@pytest.fixture
def params_list(param_name, param_values):
	return {param_name: param_values}


def test_basic(param_name, param_value, params_one):

	assert render_lambda(f'<!-- (param){param_name} -->', params_one) == f'{param_value}\n'
	assert render_lambda(f'<!-- (param){param_name} -->\n', params_one) == f'{param_value}\n'
	assert render_lambda(f'{param_value}') == f'{param_value}\n'


def test_empty_template():
	assert render_lambda('') == ''


def test_list(param_name, param_values, params_list):

	assert render_lambda(f'<!-- (param){param_name} -->', params_list) == ''.join([f'{i}\n' for i in param_values])
	assert render_lambda(f'<!-- (param){param_name} -->\n', params_list) == ''.join([f'{i}\n' for i in param_values])


def test_ref():

	addTemplate('addition', 'Nice to <!-- (param)action --> you')
	addTemplate('greeting', 'Hello, <!-- (param)name -->!\n<!-- (ref)addition -->!\n')

	assert render('greeting', {
		'name': 'username',
		'addition': {
			'action': 'eat'
		}
	}) == 'Hello, username!\nNice to eat you!\n'
	assert render('greeting', {
		'name': 'username',
		'addition': [{
			'action': 'meet'
		}, {
			'action': 'eat'
		}]
	}) == 'Hello, username!\nNice to meet you!\nNice to eat you!\n'


def test_consicutive_lines(number=2):

	for i in range(number):
		addTemplate(f'test_consicutive_lines_{i}', str(i))
	
	render_lambda(
		''.join(
			f'\t<!-- (ref)test_consicutive_lines_{i} -->\n'
			for i in range(number)
		),
		{}
	) == ''.join(
		f'\t{i}\n'
		for i in range(number)
	)


def test_optional_param():
	assert render_lambda('<!-- (optional)(param)a -->') == ''


def test_optional_ref():

	addTemplate('test_optional_ref_1', 'lalala')
	assert render_lambda('<!-- (optional)(ref)test_optional_ref_1 -->') == ''
	assert render_lambda(
		'<!-- (optional)(ref)test_optional_ref_1 -->',
		{
			'test_optional_ref_1': [None]
		}
	) == 'lalala\n'


def test_table():

	addTemplate('Row',
		'<tr>\n'
		'	<td><!-- (strict)(param)cell --></td>\n'
		'</tr>\n'
	)
	
	assert render_lambda(
		'<table>\n'
		'	<!-- (strict)(ref)Row -->\n'
		'</table>\n',
		{
			"Row": [
				{"cell": ["1.1", "2.1", "3.1"]},
				{"cell": ["1.2", "2.2", "3.2"]},
				{"cell": ["1.3", "2.3", "3.3"]}
			]
		}
	) == (
		'<table>\n'
		'	<tr>\n'
		'		<td>1.1</td>\n'
		'		<td>2.1</td>\n'
		'		<td>3.1</td>\n'
		'	</tr>\n'
		'	<tr>\n'
		'		<td>1.2</td>\n'
		'		<td>2.2</td>\n'
		'		<td>3.2</td>\n'
		'	</tr>\n'
		'	<tr>\n'
		'		<td>1.3</td>\n'
		'		<td>2.3</td>\n'
		'		<td>3.3</td>\n'
		'	</tr>\n'
		'</table>\n'
	)