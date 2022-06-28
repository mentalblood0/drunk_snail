import pytest

from drunk_snail_c import render, addTemplate

from .common import render_lambda, param_values



class Syntax:

	open = '<!--'
	close = '-->'
	optional = '(optional)'
	strict = '(strict)'
	param = '(param)'
	ref = '(ref)'


def composeParamLine(
	other_left='',
	open_tag='<!--',
	gap_left=' ',
	flag='',
	name='p',
	gap_right=' ',
	close_tag='-->',
	other_right=''
):
	return f'{other_left}{open_tag}{gap_left}{flag}(param){name}{gap_right}{close_tag}{other_right}'


other_list = ['', ' ', 'la']
gap_list = ['', ' ', '  ']
values_list = ['', 'l', 'la', '\n']

@pytest.mark.parametrize(
	'value,other_left,gap_left,gap_right,other_right',
	[
		(v, o_l, g_l, g_r, o_r)
		for v in values_list
		for o_l in other_list + [Syntax.open]
		for g_l in gap_list
		for g_r in gap_list
		for o_r in other_list + [Syntax.close]
	]
)
def test_param_correct(value, other_left, gap_left, gap_right, other_right):
	param_line = composeParamLine(
		other_left=other_left,
		gap_left=gap_left,
		gap_right=gap_right,
		other_right=other_right
	)
	assert render_lambda(param_line, {'p': value}) == f'{other_left}{value}{other_right}\n'