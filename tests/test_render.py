import pytest

from drunk_snail_python import render, addTemplate

from tests.common import render_lambda, param_values



@pytest.fixture
def param_name():
	return 'x'


@pytest.fixture
def param_value():
	return b'lalala'


@pytest.fixture
def params_one(param_name, param_value):
	return {param_name: param_value}


@pytest.fixture
def params_list(param_name, param_values):
	return {param_name: param_values}


def test_basic(param_name, param_value, params_one):

	assert render_lambda(f'<!-- (param){param_name} -->', params_one) == f'{param_value.decode()}\n'.encode('utf8')
	assert render_lambda(f'<!-- (param){param_name} -->\n', params_one) == f'{param_value.decode()}\n'.encode('utf8')
	assert render_lambda(f'{param_value}') == f'{param_value}\n'.encode('utf8')


def test_empty_template():
	assert render_lambda('') == b''


def test_list(param_name, param_values, params_list):

	assert render_lambda(f'<!-- (param){param_name} -->', params_list) == ''.join([f'{i.decode()}\n' for i in param_values]).encode('utf8')
	assert render_lambda(f'<!-- (param){param_name} -->\n', params_list) == ''.join([f'{i.decode()}\n' for i in param_values]).encode('utf8')


def test_ref():

	addTemplate('addition', 'Nice to <!-- (param)action --> you')
	addTemplate('greeting', 'Hello, <!-- (param)name -->!\n<!-- (ref)addition -->!\n')

	assert render('greeting', {
		'name': b'username',
		'addition': {
			'action': b'eat'
		}
	}) == b'Hello, username!\nNice to eat you!\n'
	assert render('greeting', {
		'name': b'username',
		'addition': [{
			'action': b'meet'
		}, {
			'action': b'eat'
		}]
	}) == b'Hello, username!\nNice to meet you!\nNice to eat you!\n'


def test_consicutive_lines(number=2):

	for i in range(number):
		addTemplate(f'test_consicutive_lines_{i}', str(i))
	
	render_lambda(
		''.join(
			f'    <!-- (ref)test_consicutive_lines_{i} -->\n'
			for i in range(number)
		),
		{}
	) == ''.join(
		f'    {i}\n'
		for i in range(number)
	).encode('utf8')


def test_optional_param():
	assert render_lambda('<!-- (optional)(param)a -->') == b''


def test_optional_ref():

	addTemplate('test_optional_ref_1', 'lalala')
	assert render_lambda('<!-- (optional)(ref)test_optional_ref_1 -->') == b''
	assert render_lambda(
		'<!-- (optional)(ref)test_optional_ref_1 -->',
		{
			'test_optional_ref_1': [None]
		}
	) == b'lalala\n'


def test_table():

	addTemplate('Row',
		'<tr>\n'
		'	<td><!-- (param)cell --></td>\n'
		'</tr>\n'
	)

	assert render_lambda(
		'<table>\n'
		'	<!-- (ref)Row -->\n'
		'</table>\n',
		{
			"Row": [
				{"cell": [b"1.1", b"2.1", b"3.1"]},
				{"cell": [b"1.2", b"2.2", b"3.2"]},
				{"cell": [b"1.3", b"2.3", b"3.3"]}
			]
		}
	) == (
		b'<table>\n'
		b'	<tr>\n'
		b'		<td>1.1</td>\n'
		b'		<td>2.1</td>\n'
		b'		<td>3.1</td>\n'
		b'	</tr>\n'
		b'	<tr>\n'
		b'		<td>1.2</td>\n'
		b'		<td>2.2</td>\n'
		b'		<td>3.2</td>\n'
		b'	</tr>\n'
		b'	<tr>\n'
		b'		<td>1.3</td>\n'
		b'		<td>2.3</td>\n'
		b'		<td>3.3</td>\n'
		b'	</tr>\n'
		b'</table>\n'
	)


def test_multiple_params():
	assert render_lambda(
		'before<!-- (param)a -->between1<!-- (param)b -->between2<!-- (param)c -->after',
		 {
			'a': b'<a>',
			'b': b'<b>',
			'c': b'<c>'
		 }
	) == b'before<a>between1<b>between2<c>after\n'


def test_multiple_params_followed_by_empty_line():
	assert render_lambda(
		'Rendering <!-- (param)size -->x<!-- (param)size --> table (mean of <!-- (param)experiments_number --> experiments)\n\n',
		{
			'size': b'10',
			'experiments_number': b'1000'
		}
	) == b'Rendering 10x10 table (mean of 1000 experiments)\n\n'