import pytest
import itertools

from .common import render_lambda



class Syntax:

	open = '<!--'
	close = '-->'
	optional = '(optional)'
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


@pytest.mark.parametrize('value', TestLists.Valid.value + sum((list(t) for t in itertools.combinations(TestLists.Valid.value, 4)), []))
@pytest.mark.parametrize('other_left', TestLists.Valid.other + [Syntax.open])
@pytest.mark.parametrize('gap_left', TestLists.Valid.gap)
@pytest.mark.parametrize('gap_right', TestLists.Valid.gap)
@pytest.mark.parametrize('other_right', TestLists.Valid.other + [Syntax.close])
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


@pytest.mark.parametrize('value', TestLists.Valid.value[:1])
@pytest.mark.parametrize('open_tag', TestLists.Invalid.open_tag)
@pytest.mark.parametrize('other_left', TestLists.Valid.other[:1])
@pytest.mark.parametrize('gap_left', TestLists.Invalid.gap)
@pytest.mark.parametrize('name', TestLists.Invalid.name)
@pytest.mark.parametrize('gap_right', TestLists.Invalid.gap)
@pytest.mark.parametrize('other_right', TestLists.Valid.other[:1])
@pytest.mark.parametrize('close_tag', TestLists.Invalid.close_tag)
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
	'lines_args',
	itertools.pairwise(
		itertools.product(
			TestLists.Valid.value, # name
			TestLists.Valid.other + [Syntax.open], # other_left
			TestLists.Valid.gap, # gap_left
			TestLists.Valid.gap, # gap_right
			TestLists.Valid.other + [Syntax.close], # other_right
		)
	)
)
def test_multiple_param_valid(lines_args):
	params_sublines = [
		composeParamLine(
			name=f'p{i}',
			other_left=a[1],
			gap_left=a[2],
			gap_right=a[3],
			other_right=a[4]
		)
		for i, a in enumerate(lines_args)
	]
	values = {
		f'p{i}': a[0]
		for i, a in enumerate(lines_args)
	}
	assert render_lambda(''.join(params_sublines), values) == ''.join((f'{a[1]}{a[0]}{a[4]}' for a in lines_args)) + '\n'


@pytest.mark.parametrize('ref', TestLists.Valid.ref)
@pytest.mark.parametrize('value', TestLists.Valid.value + sum((list(t) for t in itertools.combinations(TestLists.Valid.value, 4)), []))
@pytest.mark.parametrize('other_left', TestLists.Valid.other + [Syntax.open])
@pytest.mark.parametrize('gap_left', TestLists.Valid.gap)
@pytest.mark.parametrize('gap_right', TestLists.Valid.gap)
@pytest.mark.parametrize('other_right', TestLists.Valid.other + [Syntax.close])
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