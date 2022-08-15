import math
import functools
from sharpener_lite import Benchmark

from drunk_snail import Template
from benchmarks.common import WithOutputMetrics



class big_template(Benchmark, WithOutputMetrics):

	def prepare(self):
		self.t
		self.text
		self.t.unregister()

	@functools.cached_property
	def t(self):
		return Template('Big')

	@functools.cached_property
	def text(self):

		with open('templates/Row.xml') as f:
			text_node = f.read()

		return '\n'.join((
			text_node for i in range(
				math.ceil(
					self.config.kwargs['size_MB'] / (
						(len(text_node) + 1) / 1024 / 1024
					)
				)
			)
		))

	@property
	def output(self):
		return self.text

	def run(self):
		return self.t.register(self.text)