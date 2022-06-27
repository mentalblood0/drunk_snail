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
        {"cell": ["1", "2"]},
        {"cell": ["3", "4"]}
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

Rendering 100x100 table (mean of 10000 experiments):

| Engine                                                            | Time, ms | templates / s     |
| ----------------------------------------------------------------- | -------: | ----------------: |
| [django](https://docs.djangoproject.com/en/4.0/topics/templates/) | 34.013    | 29                |
| [chevron (mustache)](https://github.com/noahmorrison/chevron)     | 29.548    | 33                |
| [airspeed](https://github.com/purcell/airspeed)                   | 25.861    | 38                |
| [TRender](https://github.com/cesbit/trender)                      | 9.374     | 106               |
| [mako](https://github.com/sqlalchemy/mako)                        | 1.740     | 574               |
| [Jinja](https://github.com/pallets/jinja)                         | 1.412     | 708               |
| **[drunk snail](https://github.com/MentalBlood/drunk_snail)**     | **0.124** | **8064**          |

| Other                                                           | Time, ms | dicts / s |
| --------------------------------------------------------------- | -------: | --------: |
| Args dict to str                                                | 0.508     | 1968      |
| Args dict to json                                               | 0.434     | 2304      |
| Args dict to json using [orjson](https://github.com/ijl/orjson) | 0.112     | 8928      |

Rendering 1000x1000 table (mean of 100 experiments)

| Engine                                                            | Time, ms | templates / s     |
| ----------------------------------------------------------------- | -------: | ----------------: |
| [django](https://docs.djangoproject.com/en/4.0/topics/templates/) | 3443     | 0.30 ~ 0          |
| [chevron (mustache)](https://github.com/noahmorrison/chevron)     | 4950     | 0.20 ~ 0          |
| [airspeed](https://github.com/purcell/airspeed)                   | 2635     | 0.38 ~ 0          |
| [TRender](https://github.com/cesbit/trender)                      | 929      | 1                 |
| [mako](https://github.com/sqlalchemy/mako)                        | 193      | 5                 |
| [Jinja](https://github.com/pallets/jinja)                         | 213      | 4                 |
| **[drunk snail](https://github.com/MentalBlood/drunk_snail)**     | **20**   | **50**            |

| Other                                                           | Time, ms | dicts / s |
| --------------------------------------------------------------- | -------: | --------: |
| Args dict to str                                                | 52       | 19      |
| Args dict to json                                               | 54       | 18      |
| Args dict to json using [orjson](https://github.com/ijl/orjson) | 15       | 66      |

Benchmarks done using [sharpener](https://github.com/MentalBlood/sharpener) (see `Benchmarking` section below)



## Installation

```bash
pip install git+https://github.com/MentalBlood/drunk_snail
```



## Usage

```python
from drunk_snail import Template


Template('Row',
    '<tr>\n'
    '	<td><!-- (strict)(param)cell --></td>\n'
    '</tr>\n'
)
table = Template('Table',
    '<table>\n'
    '	<!-- (strict)(ref)Row -->\n'
    '</table>\n'
)

width = 10
height = 1000
args = {
    "Row": [
        {
            "cell": [
                x
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
open = '<!--';
close = '-->';

delimeter = '\n';
other = (any - delimeter)+;

param = '(param)' %action_param;
ref = '(ref)' %action_ref;
type = param | ref;

optional = '(optional)' %action_optional;
strict = '(strict)' %action_strict;
flag = optional | strict;

prefix = flag* type;
name = ([a-zA-Z_][a-zA-Z_0-9]*) >action_start_name %action_end_name;

expression = (open ' '* prefix name ' '* close) >action_start_expression %action_end_expression;

line = (other? expression? other?) >action_start_line %action_end_line;

template = (line delimeter)* (line - zlen)?;
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
    _text: str = None
)

Template.name: str
Template.text -> str

Template.__len__(self) -> int
Template.__eq__(self, other: Any) -> bool
Template.__call__(self, parameters: dict = None) -> str
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