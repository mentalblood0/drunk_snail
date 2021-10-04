from drunk_snail import Template
from drunk_snail.sources import StringSource



keywords = {
	'open_tag': '(',
	'close_tag': ')',
	'param_operator': '$',
	'ref_operator': '~'
}


def test_basic():
	
	assert Template(
		'test', 
		StringSource('( $some_param )\n'), 
		keywords
	)({
		'some_param': 'lalala'
	}) == 'lalala\n'


def test_list():

	assert Template(
		'test', 
		StringSource('( $some_param )\n'), 
		keywords
	)({
		'some_param': ['1', '2', '3']
	}) == '1\n2\n3\n'


def test_ref():

	Template(
		'addition', 
		StringSource('nice to ( $action ) you'), 
		keywords
	)

	greeting = Template(
		'greeting', 
		StringSource('Hello, ( $name ), \n( ~addition )!\n'), 
		keywords
	)
	print(greeting.compiled)
	
	result = greeting({
		'name': 'username',
		'addition': {
			'action': 'eat'
		}
	})
	print(result)
	assert result == 'Hello, username, \nnice to eat you!\n'