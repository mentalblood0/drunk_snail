import os
import pytest
from time import sleep
from drunk_snail import Template, default_keywords
from drunk_snail.sources import StringSource, FileSource



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


def test_empty_template():
	assert Template('test_render_empty_template', StringSource(''))() == ''


def test_nonexistent_file():
	with pytest.raises(FileNotFoundError):
		Template('test_render_nonexistent_file', FileSource('lalala', watch=False))


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


def test_consicutive_lines():

	t1 = Template(
		'test_consicutive_lines_1',
		StringSource('a')
	)

	t2 = Template(
		'test_consicutive_lines_2',
		StringSource('b')
	)

	t3 = Template(
		'test_consicutive_lines_3',
		StringSource('''
\t<!-- (optional)(ref)test_consicutive_lines_1 -->
\t<!-- (optional)(ref)test_consicutive_lines_2 -->
''')
	)

	result = t3({
		'test_consicutive_lines_1': {},
		'test_consicutive_lines_2': {}
	})
	assert result == '''
\ta
\tb
'''


# def test_addressing():

#     for name in [
#         'Reference',
#         'RelatesTo',
#         'ReplyTo',
#         'Relations',
#         'Addressing'
#     ]:
#         path = f"templates_/{name}.xml"
#         Template(name, FileSource(path))
	
#     result = Template('Addressing').compiled
#     assert not '(optional)(ref)ReplyTo' in result


def test_readme_example():

	# Attention! Only one operator (param or ref) on line
	# This is for intuitive handling list as param

	description = '''( $first ) template engine
( $second )er then you think'''
	d = Template('Description', StringSource(description), {
		'open_tag': '(',
		'close_tag': ')',
		'param_operator': '$'
	})

	text = '''<h1><!-- (param)header --></h1>
<div><!-- (optional)(ref)Description --></div>
<ul>
	<li><!-- (param)list_element --></li>
</ul>'''
	t = Template('Text', StringSource(text))

	parameters = {
		'header': 'Features',
		'Description': {
			'first': 'Simple',
			'second': 'Fast'
		},
		'list_element': [
			'Customizable syntax',
			'Backend written using C',
			'Auto reload template on file change'
		]
	}

	correct_result = '''<h1>Features</h1>
<div>Simple template engine</div>
<div>Faster then you think</div>
<ul>
	<li>Customizable syntax</li>
	<li>Backend written using C</li>
	<li>Auto reload template on file change</li>
</ul>'''

	assert t(parameters) == correct_result

	# --- let's reload template with new text and corresponding keywords ---

	description_with_default_keywords = '''<!-- (param)first --> template engine
<!-- (param)second -->er then you think'''

	Template(d.name, StringSource(description_with_default_keywords), default_keywords)
	assert d.text == description_with_default_keywords

	assert t(parameters) == correct_result

	# ----------- ok, let's see how to load templates from files -----------

	file_path = 'example_file.txt'

	with open(file_path, 'w') as f:
		f.write(description)

	Template(d.name, FileSource(file_path))
	
	# but there default_keywords are set, so
	assert d(parameters['Description']) == '''( $first ) template engine
( $second )er then you think'''

	# any file content change triggers template reload:
	with open(file_path, 'w') as f:
		f.write(description_with_default_keywords)
	sleep(1)
	assert d(parameters['Description']) == '''Simple template engine
Faster then you think'''

	os.remove(file_path)

	# ------------------- what about removing templates? -------------------

	d1 = Template(d.name) # description template interface copy
	d.delete()
	with pytest.raises(KeyError):
		d.text # throws KeyError
	with pytest.raises(KeyError):
		d1.text # throws KeyError too!