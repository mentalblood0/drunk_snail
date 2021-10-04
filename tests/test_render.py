from drunk_snail import Template
from drunk_snail.sources import StringSource



def test_basic():
	
	t = Template('test', StringSource('( $some_param )\n'), {
		'open_tag': '(',
		'close_tag': ')',
		'param_operator': '$'
	})

	result = t({
		'some_param': 'lalala'
	})
	
	assert result == 'lalala\n'