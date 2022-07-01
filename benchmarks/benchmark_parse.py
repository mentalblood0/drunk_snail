import math
from sharpener import Benchmark

from drunk_snail import Template



class big_template(Benchmark):

	def prepare(self, size_MB):

		if not hasattr(self, 'text'):

			self.t = Template('Big')
			with open('templates/Row.xml') as f:
				text_node = f.read()

			n = math.ceil(size_MB / ((len(text_node) + 1) / 1024 / 1024))
			self.text = '\n'.join([text_node for i in range(n)])

		else:
			self.t.unregister()

	def run(self, **kwargs):
		self.t.register(self.text)