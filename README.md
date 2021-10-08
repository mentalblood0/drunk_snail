# drunk snail

[![forthebadge](https://forthebadge.com/images/badges/made-with-c.svg)](https://forthebadge.com) [![forthebadge](https://forthebadge.com/images/badges/powered-by-black-magic.svg)](https://forthebadge.com) [![forthebadge](https://forthebadge.com/images/badges/ages-18.svg)](https://forthebadge.com)



* Template engine
* Compiles templates to Python functions
* Customizable syntax
* Auto-reload template on file change



## Installation

```bash
pip install drunk-snail
```



## Usage

```python
import os
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
```

This example is available as is in `tests/example.py` and as test in `tests/test_render.py::test_readme_example`



## Syntax

With default compilation parameters:

* `<!-- (ref)AnotherTemplateName -->` includes template(s) with name "AnotherTemplateName"
* `<!-- (param)some_param_name -->` includes param value(s)
* `<!-- (optional)(ref)AnotherTemplateName -->` skips line if no template name is provided
* `<!-- (optional)(param)some_param_name -->` skips line if no param provided

Examples can be found in git repository in `templates` directory

Default keywords:

```python
{
    'open_tag': '<!--',
    'close_tag': '-->',
    'param_operator': '(param)',
    'optional_operator': '(optional)',
    'ref_operator': '(ref)',
    'line_break': '\n'
}
```



## Resulted Python code

For template `name.xml` there will be compiled template `name.py`:

```python
def render(name):
    result = ''
    # barely readeble but fast code here
    return result
```

Parameters (`name` in example):

* It is a dictionary
* **Values might be lists**, so corresponding ref/param will be rendered for every value
* Key-value might be name and value of `param`
* Key-value might be name and parameters of `ref`
* There can be no key-value for `ref` or `param` that is `optional`
