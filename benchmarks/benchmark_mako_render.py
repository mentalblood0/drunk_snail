import functools
from sharpener_lite import Benchmark

from mako.template import Template
from benchmarks.common import WithOutputMetrics, WithName



class table(Benchmark, WithOutputMetrics, WithName):

	name = 'mako'
	link = 'https://github.com/sqlalchemy/mako'

	def prepare(self):
		self.table
		self.args

	@functools.cached_property
	def table(self):

		with open('templates/mako_template.xml', 'r', encoding='utf8') as f:
			text = f.read()

		return Template(text)

	@functools.cached_property
	def args(self):
		return {
			'rows': [
				[
					str(x + y * self.config.kwargs['width'])
					for x in range(0, self.config.kwargs['width'])
				]
				for y in range(0, self.config.kwargs['height'])
			]
		}
	
	def run(self):
		return self.table.render(**self.args)