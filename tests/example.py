from time import sleep
from drunk_snail import Template, default_keywords
from drunk_snail.sources import StringSource, FileSource

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

with open('example_file.txt', 'w') as f:
    f.write(description)

Template(d.name, FileSource('example_file.txt'))

# but there default_keywords are set, so
assert d(parameters['Description']) == '''( $first ) template engine
( $second )er then you think'''

# any file content change triggers template reload:
with open('example_file.txt', 'w') as f:
    f.write(description_with_default_keywords)
sleep(1)
assert d(parameters['Description']) == '''Simple template engine
Faster then you think'''

# -------------------- what about removing templates? --------------------

d1 = Template(d.name) # description template interface copy
d.delete()
try:
    d.text # throws KeyError
except KeyError:
    print('template is deleted')
try:
    d1.text # throws KeyError too!
except KeyError:
    print('d1 is just interface copy, not actual template copy!')