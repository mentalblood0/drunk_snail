from drunk_snail import Template
from drunk_snail.sources import StringSource



s = '<!-- (param)x -->'


def test_equality():
	
	t1 = Template('t1', StringSource(s))
	t2 = Template('t2', StringSource(s))

	assert t1 == t2


def test_length():

	t = Template('t1', StringSource(s))
	
	assert len(t) == len(s)