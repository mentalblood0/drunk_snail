import pytest
import itertools

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
	itertools.product(
		TestLists.Valid.values + sum((list(t) for t in itertools.combinations(TestLists.Valid.values, 4)), []),
		TestLists.Valid.other + [Syntax.open],
		TestLists.Valid.gap,
		TestLists.Valid.gap,
		TestLists.Valid.other + [Syntax.close]
	)
)
def test_param_valid(value, other_left, gap_left, gap_right, other_right):
	param_line = composeParamLine(
		other_left=other_left,
		gap_left=gap_left,
		gap_right=gap_right,
		other_right=other_right
	)
	assert render_lambda(param_line, {'p': value}) == (
		f'{other_left}{value}{other_right}\n'
		if type(value) == str
		else
		''.join([
			f'{other_left}{v}{other_right}\n'
			for v in value
		])
	)


@pytest.mark.parametrize(
	'value,open_tag,other_left,gap_left,name,gap_right,other_right,close_tag',
	itertools.product(
		TestLists.Valid.values[:1],
		TestLists.Invalid.open_tag,
		TestLists.Valid.other[:1],
		TestLists.Invalid.gap,
		TestLists.Invalid.name,
		TestLists.Invalid.gap,
		TestLists.Valid.other[:1],
		TestLists.Invalid.close_tag
	)
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