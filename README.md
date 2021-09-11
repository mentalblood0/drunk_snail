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

### Version 2.1

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



## Syntax

With default compilation parameters:

* `<!-- (ref)AnotherTemplateName -->` includes template(s) with name "AnotherTemplateName"
* `<!-- (param)some_param_name -->` includes param value(s)
* `<!-- (optional)(ref)AnotherTemplateName -->` skips line if no template name is provided
* `<!-- (optional)(param)some_param_name -->` skips line if no param provided

Examples can be found in git repository in `templates` directory



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
