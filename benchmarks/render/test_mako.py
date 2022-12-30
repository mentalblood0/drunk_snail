import pytest
import pathlib
import mako.template

from ..common import *



@pytest.fixture
def table(templates: pathlib.Path) -> mako.template.Template:
	return mako.template.Template((templates / 'mako_template.xml').read_text())


Args = dict[str, list[list[str]]]

@pytest.fixture
def args(table_width: int, table_height: int, cell_value: typing.Callable[[int, int], str]) -> Args:
	return {
		'rows': [
			[
				cell_value(x, y)
				for x in range(0, table_width)
			]
			for y in range(0, table_height)
		]
	}


@pytest.mark.benchmark(group='render')
def test_mako(benchmark, table: mako.template.Template, args: Args):
	benchmark(table.render, **args)