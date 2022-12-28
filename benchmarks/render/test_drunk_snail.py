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
def args(table_width: int, table_height: int) -> Args:
	return {
		"Row": [
			{
				"cell": [
					str(x + y * table_width).encode('utf8')
					for x in range(table_width)
				]
			}
			for y in range(table_height)
		]
	}


@pytest.mark.benchmark(group='render')
def test_drunk_snail(benchmark, row: Template, table: Template, args: Args):
	benchmark(table, args)