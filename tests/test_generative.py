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


class TestLists:

	class Valid:

		other = ['', ' ', 'la']
		gap = ['', ' ', '  ']
		values = ['', 'l', 'la', '\n']
	
	class Invalid:

		gap = ['l', 'la']

		open_tag = [Syntax.close] + [Syntax.open[:k] for k in range(len(Syntax.open)-1)]
		close_tag = [Syntax.open] + [Syntax.close[:k] for k in range(len(Syntax.close)-1)]

		name = ['1', '-', '1l']


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


@pytest.mark.parametrize(
	'value,other_left,gap_left,gap_right,other_right',
	[
		(v, o_l, g_l, g_r, o_r)
		for v in TestLists.Valid.values
		for o_l in TestLists.Valid.other + [Syntax.open]
		for g_l in TestLists.Valid.gap
		for g_r in TestLists.Valid.gap
		for o_r in TestLists.Valid.other + [Syntax.close]
	]
)
def test_param_valid(value, other_left, gap_left, gap_right, other_right):
	param_line = composeParamLine(
		other_left=other_left,
		gap_left=gap_left,
		gap_right=gap_right,
		other_right=other_right
	)
	assert render_lambda(param_line, {'p': value}) == f'{other_left}{value}{other_right}\n'


@pytest.mark.parametrize(
	'value,open_tag,other_left,gap_left,name,gap_right,other_right,close_tag',
	[
		(v, o_t, o_l, g_l, n, g_r, o_r, c_t)
		for v in TestLists.Valid.values[:1]
		for o_t in TestLists.Invalid.open_tag
		for o_l in TestLists.Valid.other[:1]
		for g_l in TestLists.Invalid.gap
		for n in TestLists.Invalid.name
		for g_r in TestLists.Invalid.gap
		for o_r in TestLists.Valid.other[:1]
		for c_t in TestLists.Invalid.close_tag
	]
)
def test_param_invalid(value, open_tag, other_left, gap_left, name, gap_right, other_right, close_tag):
	param_line = composeParamLine(
		open_tag=open_tag,
		other_left=other_left,
		gap_left=gap_left,
		name=name,
		gap_right=gap_right,
		other_right=other_right,
		close_tag=close_tag
	)
	assert render_lambda(param_line, {name: value}) == f'{param_line}\n'