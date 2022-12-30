import pytest
import pathlib
from drunk_snail import Template

from ..common import *



@pytest.fixture
def row(templates: pathlib.Path) -> Template:
	t = Template('Row')
	t.register((templates / 'Row.xml').read_text())
	return t


@pytest.fixture
def table(templates: pathlib.Path) -> Template:
	t = Template('Table')
	t.register((templates / 'Table.xml').read_text())
	return t


Args = dict[str, list[dict[str, list[bytes]]]]

@pytest.fixture
def args(table_width: int, table_height: int, cell_value: typing.Callable[[int, int], str]) -> Args:
	return {
		"Row": [
			{
				"cell": [
					cell_value(x, y).encode('utf8')
					for x in range(table_width)
				]
			}
			for y in range(table_height)
		]
	}


@pytest.mark.benchmark(group='render')
def test_drunk_snail(benchmark, row: Template, table: Template, args: Args):
	benchmark(table, args)