# 🌪️ drunk snail

[![forthebadge](https://forthebadge.com/images/badges/made-with-c.svg)](https://forthebadge.com) [![forthebadge](https://forthebadge.com/images/badges/powered-by-black-magic.svg)](https://forthebadge.com) [![forthebadge](https://forthebadge.com/images/badges/ages-18.svg)](https://forthebadge.com)



* Template engine
* Compiles templates to Python functions
* Customizable syntax
* Auto-reload template on file change
* Cascade reloading of referencing templates



Rendering 10x1000 table (mean of 10000 experiments):

| Engine                                                        | Time, ms |
| ------------------------------------------------------------- | -------- |
| [mako](https://github.com/sqlalchemy/mako)                    | 3.40     |
| [Jinja](https://github.com/pallets/jinja)                     | 1.64     |
| **[drunk snail](https://github.com/MentalBlood/drunk_snail)** | **1.19** |

| Other                         | Time, ms |
| ----------------------------- | -------- |
| Args dict to str              | 0.97     |
| Args dict to json             | 0.96     |
| Args dict to json with indent | 5.61     |



Rendering 100x10000 table (mean of 100 experiments)

| Engine                                                        | Time, ms |
| ------------------------------------------------------------- | -------- |
| [mako](https://github.com/sqlalchemy/mako)                    | 205      |
| [Jinja](https://github.com/pallets/jinja)                     | 216      |
| **[drunk snail](https://github.com/MentalBlood/drunk_snail)** | **86**   |

| Other                         | Time, ms |
| ----------------------------- | -------- |
| Args dict to str              | 83       |
| Args dict to json             | 73       |
| Args dict to json with indent | 313      |



Benchmarks done using [sharpener](https://github.com/MentalBlood/sharpener) (see `Benchmarking` section below)



## Installation

```bash
pip install drunk-snail
```



## Usage

```python
from drunk_snail import Template
from drunk_snail.sources import StringSource


Template('Row', StringSource(
'''<tr>
    <td><!-- (param)cell --></td>
</tr>'''
))

table = Template('Table', StringSource(
'''<table>
    <!-- (ref)Row -->
</table>'''
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

### Keywords

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

Can be set on `Template.__init__`

### Expressions

* `<!-- (ref)AnotherTemplateName -->` includes template(s) with name "AnotherTemplateName"
* `<!-- (param)some_param_name -->` includes param value(s)
* `<!-- (optional)(ref)AnotherTemplateName -->` skips line if no template name is provided
* `<!-- (optional)(param)some_param_name -->` skips line if no param provided



## Interface

```python
Template(
    self,
    name: str,
    source: Source=None,
    keywords: dict[str, str]=None,
    initial_buffer_size: int=None,
    approach: str='comprehension'
)

Template.compiled -> str
Template.text -> str
Template.source -> str
Template.name -> str
Template.keywords -> str

Template.delete(self) -> None

Template.__len__(self) -> int
Template.__eq__(self, other: _Template) -> bool
Template.__call__(self, parameters: dict) -> str
```



## Resulted Python code (`.compiled`)

For template `name.extension` there will be compiled template `name.py`:

```python
def render(name):
    return '\n'.join([
        # barely readeble but fast code here
    ])
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
python -m sharpener run
```

Config is [here](benchmarks/benchmark_default.json)