from drunk_snail import Template
from drunk_snail.sources import StringSource



def test_basic():
	
	t1 = Template('t1', StringSource('<!-- (param)x -->'))
	t2 = Template('t2', StringSource('<!-- (param)x -->'))

	assert t1 == t2