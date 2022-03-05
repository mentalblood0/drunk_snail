import drunk_snail_c
from drunk_snail import Template
from drunk_snail.sources import StringSource



def test_getTemplateRefs():

	Template(
		'test_getTemplateRefs_1',
		StringSource('lalala')
	)
	Template(
		'test_getTemplateRefs_2', 
		StringSource('<!-- (ref)test_getTemplateRefs_1 -->')
	).compiled

	assert drunk_snail_c.getTemplateRefs('test_getTemplateRefs_2') == ['test_getTemplateRefs_1']


def test_refs():

	Template(
		'test_refs_1',
		StringSource('lalala')
	)
	t = Template(
		'test_refs_2', 
		StringSource('<!-- (ref)test_refs_1 -->')
	)

	assert t.compiled and (t.refs == ['test_refs_1'])