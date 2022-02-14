import pytest

import drunk_snail_c
from drunk_snail import Template
from drunk_snail.sources import StringSource
from drunk_snail.syntax import default_keywords



keywords = {
	'open_tag': '(',
	'close_tag': ')',
	'param_operator': '$',
	'ref_operator': '~'
}

approaches = ['comprehension', 'append']


@pytest.mark.parametrize('approach', approaches)
def test_getTemplateRefs(approach: str):

	Template(
		'test_getTemplateRefs_1',
		StringSource('lalala'),
		approach=approach
	)

	Template(
		'test_getTemplateRefs_2', 
		StringSource('( ~test_getTemplateRefs_1 )'), 
		keywords,
		approach=approach
	).compiled

	assert drunk_snail_c.getTemplateRefs('test_getTemplateRefs_2') == ['test_getTemplateRefs_1']


@pytest.mark.parametrize('approach', approaches)
def test_refs(approach: str):

	t1 = Template(
		'test_refs_1',
		StringSource('lalala'),
		approach=approach
	)

	t2 = Template(
		'test_refs_2', 
		StringSource('( ~test_refs_1 )'), 
		keywords,
		approach=approach
	)

	assert t2.compiled and (t2.refs == ['test_refs_1'])