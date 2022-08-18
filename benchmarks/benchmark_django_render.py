import django
import functools
import django.conf
import django.template
from sharpener_lite import Benchmark

from benchmarks.common import WithOutputMetrics, WithName



class table(Benchmark, WithOutputMetrics, WithName):

	name = 'django'
	link = 'https://github.com/django/django'

	def prepare(self):
		self.table
		self.table_context

	@functools.cached_property
	def table(self):

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

	@functools.cached_property
	def table_context(self):
		return django.template.Context({
			'table': [
				[
					str(x)
					for x in range(self.config.kwargs['width'])
				]
				for y in range(self.config.kwargs['height'])
			]
		})
	
	def run(self):
		return self.table.render(self.table_context)