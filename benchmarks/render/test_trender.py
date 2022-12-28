import pytest
import trender

from ..common import *



@pytest.fixture
def table() -> trender.TRender:
	return trender.TRender(
		'<table>\n'
		'#for @row in @table:\n'
		'    <tr>\n'
		'#for @value in @row:\n'
		'        <td>@value</td>\n'
		'#end\n'
		'    </tr>\n'
		'#end\n'
		'</table>\n\n'
	)



Args = dict[str, list[list[str]]]

@pytest.fixture
def args(table_width: int, table_height: int) -> Args:
	return {
		'table': [
			[
				str(x + y * table_width)
				for x in range(table_width)
			]
			for y in range(table_height)
		]
	}


@pytest.mark.benchmark(group='render')
def test_trender(benchmark, table: str, args: Args):
	benchmark(table.render, args)