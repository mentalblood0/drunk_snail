# drunk snail

[![forthebadge](https://forthebadge.com/images/badges/made-with-c.svg)](https://forthebadge.com) [![forthebadge](https://forthebadge.com/images/badges/powered-by-black-magic.svg)](https://forthebadge.com) [![forthebadge](https://forthebadge.com/images/badges/ages-18.svg)](https://forthebadge.com)



* Template engine
* Compiles templates to Python functions
* Customizable syntax



## Installation

```bash
pip install drunk-snail
```



## Usage

### Version 1.6

#### From code

```python
from drunk_snail import *

# default arguments
compileTemplates(
    input_dir='templates', 
    output_dir='compiled_templates',
    open_tag='<!--',
    close_tag='-->',
    param_operator='(param)',
    ref_operator='(ref)',
    optional_operator='(optional)',
    log=0 # set 1 to enable logging to stdout
)
```

#### From command line

```bash
python -m drunk_snail -h
```

### Versions 2.1, 2.6

Compiling files:

```python
from drunk_snail import *

# referenced in template 'EncryptedKey'
addTemplate('IssuerSerial', 'templates/IssuerSerial.xml')
addTemplate('DataReference', 'templates/DataReference.xml')

addTemplate('EncryptedKey', 'templates/EncryptedKey.xml')

result = compile('EncryptedKey') # returns resulted function text
```

Compiling strings:

```python
from drunk_snail import *

# referenced in template 'EncryptedKey'
addTemplate('IssuerSerial', 'templates/IssuerSerial.xml')
addTemplate('DataReference', 'templates/DataReference.xml')

with open('templates/EncryptedKey.xml') as f:
    s = f.read()

# second argument is resulted function name (default is '_temp')
result = compileString(s, 'EncryptedKey')
```

### Version 2.6

Setting keywords to use in templates compilation:

````python
setKeyword('open_tag', '(')
setKeyword('close_tag', ')')
setKeyword('param_operator', '$')
setKeyword('optional_operator' '?')
setKeyword('ref_operator', '~')

# Of course, keywords might consists of more than one character
# For example, here is defaults:
setKeyword('open_tag', '<!--')
setKeyword('close_tag', '-->')
setKeyword('param_operator', '(param)')
setKeyword('optional_operator' '(optional)')
setKeyword('ref_operator', '(ref)')
````

**Attention**: if there references to other templates, these templates must have the same syntax as root template

In the future I'm going to add the ability to use different syntaxes for templates that references each other

### Version 3.0

Adding templates:

```python
from drunk_snail import *

addTemplate(
    'CanonicalizationMethod', # name
    'templates/CanonicalizationMethod_another_syntax.xml', # file path
    { # custom keywords (optional)
        'open_tag': '(',
        'close_tag': ')',
        'param_operator': '[purum]',
        'optional_operator': '{optionalno}'
    }
)
```

Setting template-specific keywords:

```python
from drunk_snail import *

addTemplate('IssuerSerial', 'templates/IssuerSerial_another_syntax__one_character_keywords.xml')
addTemplate('EncryptedKey', 'templates/EncryptedKey_another_syntax__one_character_keywords.xml')

one_character_keywords = {
    'open_tag': '(',
    'close_tag': ')',
    'param_operator': '$',
    'optional_operator': '?',
    'ref_operator': '~'
}

setKeywords('EncryptedKey', one_character_keywords)
setKeywords('IssuerSerial', one_character_keywords)

# or:
setKeywords(['EncryptedKey', 'IssuerSerial'], one_character_keywords)
```



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
