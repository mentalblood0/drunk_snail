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
		StringSource('( $x )'), 
		keywords
	)({
		'x': 'lalala'
	}) == 'lalala'

	assert Template(
		'test', 
		StringSource('( $x )\n')
	)({
		'x': 'lalala'
	}) == 'lalala\n'

	assert Template(
		'test', 
		StringSource('lalala')
	)({}) == 'lalala'


def test_list():

	assert Template(
		'test', 
		StringSource('( $some_param )\n'), 
		keywords
	)({
		'some_param': ['1', '2', '3']
	}) == '1\n2\n3\n'

	assert Template(
		'test', 
		StringSource('( $some_param )'), 
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

	Template(
		'greeting', 
		StringSource('Hello, ( $name )!\n( ~addition )!\n'), 
		keywords
	)
	
	assert Template('greeting')({
		'name': 'username',
		'addition': {
			'action': 'eat'
		}
	}) == 'Hello, username!\nNice to eat you!\n'

	print(Template('greeting').compiled)

	result = Template('greeting')({
		'name': 'username',
		'addition': [{
			'action': 'meet'
		}, {
			'action': 'eat'
		}]
	})
	print(result)
	assert result == 'Hello, username!\nNice to meet you!\nNice to eat you!\n'