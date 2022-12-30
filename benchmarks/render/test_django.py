import pytest
import django
import django.conf
import django.template

from ..common import *



@pytest.fixture
def table() -> django.template.Template:

	django.conf.settings.configure(TEMPLATES=[{
		'BACKEND': 'django.template.backends.django.DjangoTemplates'
	}])
	django.setup()

	return django.template.Template(
		'<table>\n'
		'{% for row in table %}'
		'    <tr>'
		'{% for value in row %}\n'
		'        <td>{{ value }}</td>'
		'{% endfor %}\n'
		'    </tr>\n'
		'{% endfor %}'
		'</table>\n'
	)


@pytest.fixture
def args(table_width: int, table_height: int, cell_value: typing.Callable[[int, int], str]) -> django.template.Context:
	return django.template.Context({
		'table': [
			[
				cell_value(x, y)
				for x in range(table_width)
			]
			for y in range(table_height)
		]
	})


@pytest.mark.benchmark(group='render')
def test_django(benchmark, table: django.template.Template, args: django.template.Context):
	benchmark(table.render, args)