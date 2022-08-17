# 🌪️ drunk snail

[![forthebadge](https://forthebadge.com/images/badges/made-with-c.svg)](https://forthebadge.com) [![forthebadge](https://forthebadge.com/images/badges/powered-by-black-magic.svg)](https://forthebadge.com) [![forthebadge](https://forthebadge.com/images/badges/ages-18.svg)](https://forthebadge.com)



## Why?

* <!-- (param)why -->



## Example

Row:
```html
<!-- (param)row_template -->
```
Table:
```html
<!-- (param)table_template -->
```
Arguments:
```json
<!-- (param)table_arguments -->
```
Result:
```html
<!-- (param)table_result -->
```



## Performance

<!-- (ref)TableRenderingResults -->



## Installation

```bash
pip install git+<!-- (param)git_link -->
```



## Usage

```python
from drunk_snail import Template


Template('Row').register(
'''<!-- (param)row_template -->'''
)
table = Template('Table').register(
'''<!-- (param)table_template -->'''
)

args = <!-- (param)table_arguments -->

result = table(args)
assert result == '''<!-- (param)table_result -->'''
```



## Syntax

Line may have:

* 0 parameter expressions and 0 reference expressions
* Any number of parameter expressions and 0 reference expressions
* 0 parameter expressions and 1 reference expression

```
<!-- (param)syntax -->
```


### Examples

<!-- (ref)Example -->



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
pip install --upgrade git+<!-- (param)git_link -->
git clone <!-- (param)git_link -->
cd drunk_snail
pytest
```



## Benchmarking

Using [sharpener_lite](https://github.com/MentalBlood/sharpener_lite):

```bash
pip install --upgrade git+<!-- (param)git_link -->
git clone <!-- (param)git_link --> drunk_snail
cd drunk_snail
python -m sharpener_lite
```

Config is [here](benchmarks/benchmark_default.json)



## Binding to other languages

1. You will need [this folder](drunk_snail/drunk_snail_python/modules/drunk_snail_c)
2. Edit [parameters-related macros](drunk_snail/drunk_snail_python/modules/drunk_snail_c/include/params_macros.h)
3. Add bindings for [adding](drunk_snail/drunk_snail_python/modules/drunk_snail_c/include/addTemplate.h), [getting](drunk_snail/drunk_snail_python/modules/drunk_snail_c/include/getTemplate.h), [removing](drunk_snail/drunk_snail_python/modules/drunk_snail_c/include/removeTemplate.h) and [rendering](drunk_snail/drunk_snail_python/modules/drunk_snail_c/include/render.h) to your language