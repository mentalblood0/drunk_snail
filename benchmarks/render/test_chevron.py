import pytest
import chevron

from ..common import *



@pytest.fixture
def table() -> str:
	return (
		'<table>\n'
		'{{#Row}}\n'
		'    <tr>\n'
		'{{#cell}}\n'
		'        <td>{{value}}</td>\n'
		'{{/cell}}\n'
		'    </tr>\n'
		'{{/Row}}\n'
		'</table>\n'
	)



Args = dict[str, list[dict[str, list[dict[str, str]]]]]

@pytest.fixture
def args(table_width: int, table_height: int) -> Args:
	return {
		"Row": [
			{
				"cell": [
					{
						'value': str(x + y * table_width)
					}
					for x in range(table_width)
				]
			}
			for y in range(table_height)
		]
	}


@pytest.mark.benchmark(group='render')
def test_chevron(benchmark, table: str, args: Args):
	benchmark(chevron.render, table, args)