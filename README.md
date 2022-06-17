# 🌪️ drunk snail

[![forthebadge](https://forthebadge.com/images/badges/made-with-c.svg)](https://forthebadge.com) [![forthebadge](https://forthebadge.com/images/badges/powered-by-black-magic.svg)](https://forthebadge.com) [![forthebadge](https://forthebadge.com/images/badges/ages-18.svg)](https://forthebadge.com)



## Why?

* Faster
* Easy-readable syntax
* Separation of business logic and data



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

| Engine                                                            | Time, ms | templates / s     |
| ----------------------------------------------------------------- | -------- | ----------------- |
| [django](https://docs.djangoproject.com/en/4.0/topics/templates/) | 39.54    | 25                |
| [chevron (mustache)](https://github.com/noahmorrison/chevron)     | 30.93    | 32                |
| [mako](https://github.com/sqlalchemy/mako)                        | 3.08     | 324               |
| [Jinja](https://github.com/pallets/jinja)                         | 1.56     | 641               |
| **[drunk snail](https://github.com/MentalBlood/drunk_snail)**     | **0.44** | **2272**          |

| Other                         | Time, ms | dicts / s |
| ----------------------------- | -------- | --------- |
| Args dict to str              | 0.88     | 1136      |
| Args dict to json             | 0.80     | 1249      |
| Args dict to json with indent | 5.13     | 194       |

Rendering 100x10000 table (mean of 100 experiments)

| Engine                                                            | Time, ms | templates / s     |
| ----------------------------------------------------------------- | -------- | ----------------- |
| [django](https://docs.djangoproject.com/en/4.0/topics/templates/) | 3380     | 0 (0.30)          |
| [chevron (mustache)](https://github.com/noahmorrison/chevron)     | 13945    | 0 (0.07)          |
| [mako](https://github.com/sqlalchemy/mako)                        | 198      | 5                 |
| [Jinja](https://github.com/pallets/jinja)                         | 203      | 4                 |
| **[drunk snail](https://github.com/MentalBlood/drunk_snail)**     | **39**   | **25**            |

| Other                         | Time, ms | dicts / s |
| ----------------------------- | -------- | --------- |
| Args dict to str              | 75       | 13        |
| Args dict to json             | 66       | 16        |
| Args dict to json with indent | 297      | 3         |

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
    source: Source
)

Template.text -> str
Template.source -> str
Template.name -> str

Template.reload(self, source: Source = None) -> int
Template.delete(self) -> None

Template.__len__(self) -> int
Template.__eq__(self, other: _Template) -> bool
Template.__call__(self, parameters: dict) -> str
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