import pytest
import itertools

from .common import render_lambda



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
		value = ['', 'l', 'la', '\n']

		ref = [
			f'{Syntax.open}{Syntax.param}p{Syntax.close}'
		]

		one_line_params_number = [2, 3]

	class Invalid:

		gap = ['l', 'la']

		open_tag = [Syntax.close] + [Syntax.open[:k] for k in range(len(Syntax.open)-1)]
		close_tag = [Syntax.open] + [Syntax.close[:k] for k in range(len(Syntax.close)-1)]

		name = ['1', '-', '1l']


def composeLine(
	type,
	name,
	other_left='',
	open_tag=Syntax.open,
	gap_left=' ',
	flag='',
	gap_right=' ',
	close_tag=Syntax.close,
	other_right=''
):
	return ''.join([other_left, open_tag, gap_left, flag, type, name, gap_right, close_tag, other_right])


def composeParamLine(*args, name='p', **kwargs):
	return composeLine(type=Syntax.param, name=name, *args, **kwargs)


def composeRefLine(*args, name='R', **kwargs):
	return composeLine(type=Syntax.ref, name=name, *args, **kwargs)


@pytest.mark.parametrize(
	'value,other_left,gap_left,gap_right,other_right',
	itertools.product(
		TestLists.Valid.value + sum((list(t) for t in itertools.combinations(TestLists.Valid.value, 4)), []),
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
		TestLists.Valid.value[:1],
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


@pytest.mark.parametrize(
	'value,other_left,gap_left,gap_right,other_right,n',
	itertools.product(
		TestLists.Valid.value + sum((list(t) for t in itertools.combinations(TestLists.Valid.value, 4)), []),
		TestLists.Valid.other + [Syntax.open],
		TestLists.Valid.gap,
		TestLists.Valid.gap,
		TestLists.Valid.other + [Syntax.close],
		TestLists.Valid.one_line_params_number
	)
)
def test_multiple_param_valid(value, other_left, gap_left, gap_right, other_right, n):
	params_line = composeParamLine(
		other_left=other_left,
		gap_left=gap_left,
		gap_right=gap_right,
		other_right=other_right
	) * n
	assert render_lambda(params_line, {'p': value}) == (
		(f'{other_left}{value}{other_right}' * n + '\n')
		if type(value) == str
		else
		''.join([
			(f'{other_left}{v}{other_right}' * n + '\n')
			for v in value
		])
	)


@pytest.mark.parametrize(
	'ref,value,other_left,gap_left,gap_right,other_right',
	itertools.product(
		TestLists.Valid.ref,
		TestLists.Valid.value + sum((list(t) for t in itertools.combinations(TestLists.Valid.value, 4)), []),
		TestLists.Valid.other + [Syntax.open],
		TestLists.Valid.gap,
		TestLists.Valid.gap,
		TestLists.Valid.other + [Syntax.close]
	)
)
def test_ref_valid(ref, value, other_left, gap_left, gap_right, other_right):
	ref_line = composeRefLine(
		other_left=other_left,
		gap_left=gap_left,
		gap_right=gap_right,
		other_right=other_right
	)
	assert render_lambda(ref_line, {'R': {'p': value}}, {'R': ref}) == (
		f'{other_left}{value}{other_right}\n'
		if type(value) == str
		else
		''.join([
			f'{other_left}{v}{other_right}\n'
			for v in value
		])
	)