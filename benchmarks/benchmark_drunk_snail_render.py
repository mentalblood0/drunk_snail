import functools
from sharpener_lite import Benchmark

from drunk_snail import Template
from benchmarks.common import WithOutputMetrics, WithTableArgs



class table(Benchmark, WithOutputMetrics, WithTableArgs):

	@functools.cached_property
	def row(self):
		result = Template('Row')
		with open('templates/Row.xml') as f:
			result.register(f.read())
		return result

	@functools.cached_property
	def table(self):
		self.row
		result = Template('Table')
		with open('templates/Table.xml') as f:
			result.register(f.read())
		return result

	def prepare(self):
		self.row
		self.table
		self.args

	def run(self):
		return self.table(self.args)