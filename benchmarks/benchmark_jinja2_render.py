import functools
from jinja2 import Environment
from sharpener_lite import Benchmark

from benchmarks.common import WithOutputMetrics, WithName



class table(Benchmark, WithOutputMetrics, WithName):

	name = 'jinja'
	link = 'https://github.com/pallets/jinja'

	def prepare(self):
		self.table
		self.args

	@functools.cached_property
	def table(self):
		return Environment().from_string(
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

	@functools.cached_property
	def args(self):
		return {
			'rows':[
				[
					str(x + y * self.config.kwargs['width'])
					for x in range(self.config.kwargs['width'])
				]
				for y in range(self.config.kwargs['height'])
			]
		}
	
	def run(self):
		return self.table.render(**self.args)