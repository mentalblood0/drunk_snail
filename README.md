# 🌪️ drunk snail

[![forthebadge](https://forthebadge.com/images/badges/made-with-c.svg)](https://forthebadge.com) [![forthebadge](https://forthebadge.com/images/badges/powered-by-black-magic.svg)](https://forthebadge.com) [![forthebadge](https://forthebadge.com/images/badges/ages-18.svg)](https://forthebadge.com)



* Template engine
* Compiles templates to Python functions
* Templates hot reloading
* Automatic reloading on file change
* Cascade reloading of referencing templates



## Example

Row:
```html
<tr>
    <td><!-- (param)cell --></td>
</tr>
```
Table:
```html
<table>
    <!-- (ref)Row -->
</table>
```
Arguments:
```json
{
    "Row": [
        {"cell": ["1.1", "2.1"]},
        {"cell": ["1.2", "2.2"]}
    ]
}
```
Result:
```html
<table>
    <tr>
        <td>1.1</td>
        <td>2.1</td>
    </tr>
    <tr>
        <td>1.2</td>
        <td>2.2</td>
    </tr>
</table>
```



## Performance

Rendering 10x1000 table (mean of 10000 experiments):

| Engine                                                                                     | Time, ms |
| ------------------------------------------------------------------------------------------ | -------- |
| [mako](https://github.com/sqlalchemy/mako)                                                 | 3.23     |
| [Jinja](https://github.com/pallets/jinja)                                                  | 1.64     |
| **[drunk snail](https://github.com/MentalBlood/drunk_snail)**                              | **0.96** |
| **[drunk snail](https://github.com/MentalBlood/drunk_snail)** (parameters dimension cache) | **0.67** |

| Other                         | Time, ms |
| ----------------------------- | -------- |
| Args dict to str              | 0.91     |
| Args dict to json             | 0.81     |
| Args dict to json with indent | 5.25     |

Rendering 100x10000 table (mean of 100 experiments)

| Engine                                                        | Time, ms |
| ------------------------------------------------------------- | -------- |
| [mako](https://github.com/sqlalchemy/mako)                    | 198      |
| [Jinja](https://github.com/pallets/jinja)                     | 204      |
| **[drunk snail](https://github.com/MentalBlood/drunk_snail)** | **79**   |

| Other                         | Time, ms |
| ----------------------------- | -------- |
| Args dict to str              | 76       |
| Args dict to json             | 68       |
| Args dict to json with indent | 302      |

Benchmarks done using [sharpener](https://github.com/MentalBlood/sharpener) (see `Benchmarking` section below)



## Installation

```bash
pip install git+https://github.com/MentalBlood/drunk_snail
```



## Usage

```python
from drunk_snail import Template
from drunk_snail.sources import StringSource


Template('Row', StringSource(
    '<tr>\n'
    '    <td><!-- (param)cell --></td>\n'
    '</tr>\n'
))

table = Template('Table', StringSource(
    '<table>\n'
    '    <!-- (ref)Row -->\n'
    '</table>\n'
))

width = 10
height = 1000
args = {
    "Row": [
        {
            "cell": [
                f"{x}.{y}"
                for x in range(width)
            ]
        }
        for y in range(height)
    ]
}

result = table(args)
print(result)
```



## Syntax

```
open = '<!--'
close = '-->'

param = '(param)'
ref = '(ref)'
optional = '(optional)'
strict = '(strict)'

operator = param | ref | optional | strict

name = [a-zA-Z_][a-zA-Z_0-9]*

expression = open ' '* operator+ name ' '* close

delimeter = '\n'
other = (any - delimeter)+

line = other? expression? other?

template = (line delimeter)* (line - zlen)?
```


### Examples

* `<!-- (ref)AnotherTemplateName -->` includes template(s) with name "AnotherTemplateName"
* `<!-- (param)some_param_name -->` includes param value(s)
* `<!-- (optional)(ref)AnotherTemplateName -->` skips line if no template name is provided
* `<!-- (optional)(param)some_param_name -->` skips line if no param provided
* `<!-- (strict)(ref)AnotherTemplateName -->` corresponding object must be list[dict]
* `<!-- (strict)(param)some_param_name -->` corresponding object must be list[string]



## Interface

```python
Template(
    self,
    name: str,
    source: Source=None
)

Template.compiled -> str
Template.text -> str
Template.source -> str
Template.name -> str

Template.delete(self) -> None

Template.__len__(self) -> int
Template.__eq__(self, other: _Template) -> bool
Template.__call__(self, parameters: dict) -> str
```



## Resulted Python code (`.compiled`)

For template `name.extension` there will be compiled template `name.py`:

```python
J='\n'.join
def render(name):
    return J([<barely readeble but fast code here>])
```

Parameters:

```python
name = dict[str, None | str | Iterable['name'] | list[Iterable['name']]]
```



## Testing

Using [pytest](https://pypi.org/project/pytest/):

```bash
pip install --upgrade drunk_snail
git clone https://github.com/MentalBlood/drunk_snail drunk_snail
cd drunk_snail
pytest
```



## Benchmarking

Using [sharpener](https://github.com/MentalBlood/sharpener):

```bash
pip install --upgrade drunk_snail
git clone https://github.com/MentalBlood/drunk_snail drunk_snail
cd drunk_snail
python -m sharpener run -p 0
```

Config is [here](benchmarks/benchmark_default.json)