import pytest
import airspeed

from ..common import *



@pytest.fixture
def table():
	return airspeed.Template(
		'<table>\n'
		'#foreach ($row in $table)'
		'    <tr>\n'
		'#foreach ($value in $row)'
		'        <td>$value</td>\n'
		'#end'
		'    </tr>\n'
		'#end'
		'</table>\n'
	)


Args = dict[str, list[list[str]]]

@pytest.fixture
def args(table_width: int, table_height: int) -> Args:
	return {
		'table': [
			[
				str(object = x + y * table_width)
				for x in range(table_width)
			]
			for y in range(table_height)
		]
	}


@pytest.mark.benchmark(group='render')
def test_airspeed(benchmark, table: airspeed.Template, args: Args):
	benchmark(table.merge, args)