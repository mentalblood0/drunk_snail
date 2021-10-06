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
		'test_render_basic', 
		StringSource('( $x )'), 
		keywords
	)({
		'x': 'lalala'
	}) == 'lalala'

	assert Template(
		'test_render_basic', 
		StringSource('( $x )\n')
	)({
		'x': 'lalala'
	}) == 'lalala\n'

	assert Template(
		'test_render_basic', 
		StringSource('lalala')
	)({}) == 'lalala'


def test_list():

	assert Template(
		'test_render_list', 
		StringSource('( $some_param )\n'), 
		keywords
	)({
		'some_param': ['1', '2', '3']
	}) == '1\n2\n3\n'

	assert Template(
		'test_render_list', 
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


def test_buf_overflow():

	t1 = Template(
		'test_buf_overflow_1', 
		StringSource(' ' * 1000),
		keywords
	)

	t2 = Template(
		'test_buf_overflow_2', 
		StringSource('( ~test_buf_overflow_1 )'),
		keywords
	)

	assert t2.compiled