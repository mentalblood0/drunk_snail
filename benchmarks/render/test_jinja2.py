import pytest
import jinja2

from ..common import *



@pytest.fixture
def table() -> jinja2.Template:
	return jinja2.Environment().from_string(
		'<table>\n'
		'{% for row in rows %}'
			'    <tr>\n'
		'{% for cell in row %}'
				'        <td>{{ cell }}</td>\n'
		'{% endfor %}'
			'    </tr>\n'
		'{% endfor %}'
		'</table>\n\n'
	)


Args = dict[str, list[list[str]]]

@pytest.fixture
def args(table_width: int, table_height: int, cell_value: typing.Callable[[int, int], str]) -> Args:
	return {
		'rows':[
			[
				cell_value(x, y)
				for x in range(table_width)
			]
			for y in range(table_height)
		]
	}


@pytest.mark.benchmark(group='render')
def test_jinja2(benchmark, table: jinja2.Template, args: Args):
	benchmark(table.render, **args)