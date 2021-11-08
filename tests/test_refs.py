import drunk_snail_c
from drunk_snail.sources import StringSource
from drunk_snail import Template, default_keywords



keywords = {
	'open_tag': '(',
	'close_tag': ')',
	'param_operator': '$',
	'ref_operator': '~'
}


def test_getTemplateRefs():

	Template(
		'test_getTemplateRefs_1',
		StringSource('lalala')
	)

	Template(
		'test_getTemplateRefs_2', 
		StringSource('( ~test_getTemplateRefs_1 )'), 
		keywords
	).compiled

	assert drunk_snail_c.getTemplateRefs('test_getTemplateRefs_2') == ['test_getTemplateRefs_1']


def test_refs():

	t1 = Template(
		'test_refs_1',
		StringSource('lalala')
	)

	t2 = Template(
		'test_refs_2', 
		StringSource('( ~test_refs_1 )'), 
		keywords
	)

	assert t2.compiled and (t2.refs == ['test_refs_1'])