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
		StringSource('Nice to ( $action ) you'), 
		keywords
	)

	greeting = Template(
		'greeting', 
		StringSource('Hello, ( $name )!\n( ~addition )!\n'), 
		keywords
	)
	
	assert greeting({
		'name': 'username',
		'addition': {
			'action': 'eat'
		}
	}) == 'Hello, username!\nNice to eat you!\n'

	result = greeting({
		'name': 'username',
		'addition': [{
			'action': 'meet'
		}, {
			'action': 'eat'
		}]
	})
	print(result)
	assert result == 'Hello, username!\nNice to meet you!\nNice to eat you!\n'