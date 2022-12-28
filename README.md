# 🌪️ drunk snail



## Why?

* Faster
* Easy syntax
* Separates logic and data



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
```python
{
    "Row": [
        {
            "cell": [
                b"1",
                b"2"
            ]
        },
        {
            "cell": [
                b"3",
                b"4"
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

OS: Windows 10.0.22000

CPU: AMD64 Family 25 Model 33 Stepping 2, AuthenticAMD

Python: 3.11.0

Rendering 100x100 table (mean of 100-10000 experiments)

| Engine | Time, ms  | templates / s | output, MB / s |
| -- | --: | --: | --: |
| [chevron](https://github.com/noahmorrison/chevron) | 24.139 | 41 | 9.147 |
| [django](https://github.com/django/django) | 20.549 | 48 | 10.745 |
| [airspeed](https://github.com/purcell/airspeed) | 17.258 | 57 | 12.795 |
| [TRender](https://github.com/cesbit/trender) | 6.470 | 154 | 34.126 |
| [jinja](https://github.com/pallets/jinja) | 1.127 | 887 | 195.930 |
| [mako](https://github.com/sqlalchemy/mako) | 1.058 | 945 | 208.622 |
| [drunk_snail](https://github.com/MentalBlood/drunk_snail) | 0.089 | 11235 | 2494.516 |

| Other | Time, ms  | dicts / s | output, MB / s |
| -- | --: | --: | --: |
| Arguments to JSON | 0.507 | 1972 | 158.070 |
| Arguments to string | 0.379 | 2638 | 237.625 |
| [Arguments to JSON using orjson](https://github.com/ijl/orjson) | 0.099 | 10101 | 709.556 |


See [`Testing/Benchmarking`](#testingbenchmarking) section to reproduce



## Installation

```bash
pip install git+https://github.com/MentalBlood/drunk_snail
```



## Usage

```python
from drunk_snail import Template


Template('Row').register(
'''<tr>
    <td><!-- (param)cell --></td>
</tr>'''
)
table = Template('Table')
table.register(
'''<table>
    <!-- (ref)Row -->
</table>'''
)

args = {
    "Row": [
        {
            "cell": [
                b"1",
                b"2"
            ]
        },
        {
            "cell": [
                b"3",
                b"4"
            ]
        }
    ]
}

result = table(args)
assert result == b'''<table>
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
flag = optional
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



## Interface

```python
Template(name: str)

Template.name: str
Template.text: bytes

Template.register(self, text: str) -> None
Template.unregister(self) -> None

Template.__call__(self, parameters: dict = None, detect_recursion: bool = False) -> bytes
```



## Testing/Benchmarking

Using [pytest](https://pypi.org/project/pytest/) and [pytest-benchmark](https://github.com/ionelmc/pytest-benchmark):

```bash
pip install --upgrade git+https://github.com/MentalBlood/drunk_snail
git clone https://github.com/MentalBlood/drunk_snail
cd drunk_snail
pytest
```



## Binding to other languages

1. You will need [this folder](drunk_snail/drunk_snail_python/modules/drunk_snail_c)
2. Edit [parameters-related macros](drunk_snail/drunk_snail_python/modules/drunk_snail_c/include/params_macros.h)
3. Add bindings for [adding](drunk_snail/drunk_snail_python/modules/drunk_snail_c/include/addTemplate.h), [getting](drunk_snail/drunk_snail_python/modules/drunk_snail_c/include/getTemplate.h), [removing](drunk_snail/drunk_snail_python/modules/drunk_snail_c/include/removeTemplate.h) and [rendering](drunk_snail/drunk_snail_python/modules/drunk_snail_c/include/render.h) to your language
