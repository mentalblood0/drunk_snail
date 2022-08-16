import functools
from jinja2 import Environment
from sharpener_lite import Benchmark

from benchmarks.common import WithOutputMetrics



class table(Benchmark, WithOutputMetrics):

	def prepare(self):
		self.table
		self.args

	@functools.cached_property
	def table(self):
		return Environment().from_string(
			'<table>\n'
			'{% for row in rows %}'
				'\t<tr>\n'
			'{% for cell in row %}'
					'\t\t<td>{{ cell }}</td>\n'
			'{% endfor %}'
				'\t</tr>\n'
			'{% endfor %}'
			'</table>'
		)

	@functools.cached_property
	def args(self):
		return {
			'rows':[
				[
					str(x)
					for x in range(self.config.kwargs['width'])
				]
				for y in range(self.config.kwargs['height'])
			]
		}
	
	def run(self):
		return self.table.render(**self.args)