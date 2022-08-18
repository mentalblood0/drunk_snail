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
    <td><!-- (strict)(param)cell --></td>
</tr>
```
Table:
```html
<table>
    <!-- (strict)(ref)Row -->
</table>
```
Arguments:
```json
{
    "Row": [
        {
            "cell": [
                "1",
                "2"
            ]
        },
        {
            "cell": [
                "3",
                "4"
            ]
        }
    ]
}
```
Result:
```html
<table>
    <tr>
        <td>1</td>
        <td>2</td>
    </tr>
    <tr>
        <td>3</td>
        <td>4</td>
    </tr>
</table>

```



## Performance

Rendering 100x100 table (mean of 100-10000 experiments)

| Engine | Time, ms  | templates / s | output, MB / s |
| -- | --: | --: | --: |
| [django](https://github.com/django/django) | 31.72 | 31 | 6.33 |
| [chevron](https://github.com/noahmorrison/chevron) | 29.71 | 33 | 6.76 |
| [airspeed](https://github.com/purcell/airspeed) | 26.122 | 38 | 7.69 |
| [TRender](https://github.com/cesbit/trender) | 9.37 | 106 | 21.45 |
| [jinja](https://github.com/pallets/jinja) | 1.47 | 680 | 137.138 |
| [mako](https://github.com/sqlalchemy/mako) | 1.4 | 714 | 143.99 |
| [drunk_snail](https://github.com/MentalBlood/drunk_snail) | 0.142 | 7042 | 1411.95 |

| Other | Time, ms  | dicts / s | output, MB / s |
| -- | --: | --: | --: |
| Arguments to string | 0.5 | 2000 | 120.242 |
| Arguments to JSON | 0.43 | 2325 | 139.6 |
| [Arguments to JSON using orjson](https://github.com/ijl/orjson) | 0.11 | 9090 | 456.79 |


Benchmarks done using [sharpener_lite](https://github.com/MentalBlood/sharpener_lite) (see [`Benchmarking`](#benchmarking) section below)



## Installation

```bash
pip install git+https://github.com/MentalBlood/drunk_snail
```



## Usage

```python
from drunk_snail import Template


Template('Row').register(
'''<tr>
    <td><!-- (strict)(param)cell --></td>
</tr>'''
)
table = Template('Table')
table.register(
'''<table>
    <!-- (strict)(ref)Row -->
</table>'''
)

args = {
    "Row": [
        {
            "cell": [
                "1",
                "2"
            ]
        },
        {
            "cell": [
                "3",
                "4"
            ]
        }
    ]
}

result = table(args)
assert result == '''<table>
    <tr>
        <td>1</td>
        <td>2</td>
    </tr>
    <tr>
        <td>3</td>
        <td>4</td>
    </tr>
</table>
'''
```



## Syntax

Line may have:

| parameters | references |
| ---------- | ---------- |
| *          | 0          |
| 0          | 1          |

```
open = '<!--'
close = '-->'
delimeter = '\n'
other = (any - delimeter)+
param = '(param)'
ref = '(ref)'
type = param | ref
optional = '(optional)'
strict = '(strict)'
flag = optional | strict
name = ([a-zA-Z_][a-zA-Z_0-9]*)
param_expression = (open ' '* flag? param name ' '* close)
ref_expression = (open ' '* flag? ref name ' '* close)
expressions = ((param_expression other?)+ | (ref_expression other?))
line = (other? expressions?)
template = (line delimeter)* (line - zlen)?
main := template
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
Template(name: str)

Template.name: str
Template.text: str

Template.register(self, text: str) -> None
Template.unregister(self) -> None

Template.__call__(self, parameters: dict = None) -> str
```



## Testing

Using [pytest](https://pypi.org/project/pytest/):

```bash
pip install --upgrade git+https://github.com/MentalBlood/drunk_snail
git clone https://github.com/MentalBlood/drunk_snail
cd drunk_snail
pytest
```



## Benchmarking

Using [sharpener_lite](https://github.com/MentalBlood/sharpener_lite):

```bash
pip install --upgrade git+https://github.com/MentalBlood/drunk_snail
git clone https://github.com/MentalBlood/drunk_snail drunk_snail
cd drunk_snail
python -m sharpener_lite
```

Config is [here](benchmarks/benchmark_default.json)



## Binding to other languages

1. You will need [this folder](drunk_snail/drunk_snail_python/modules/drunk_snail_c)
2. Edit [parameters-related macros](drunk_snail/drunk_snail_python/modules/drunk_snail_c/include/params_macros.h)
3. Add bindings for [adding](drunk_snail/drunk_snail_python/modules/drunk_snail_c/include/addTemplate.h), [getting](drunk_snail/drunk_snail_python/modules/drunk_snail_c/include/getTemplate.h), [removing](drunk_snail/drunk_snail_python/modules/drunk_snail_c/include/removeTemplate.h) and [rendering](drunk_snail/drunk_snail_python/modules/drunk_snail_c/include/render.h) to your language
