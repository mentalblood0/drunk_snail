from sharpener import Benchmark

from drunk_snail import Template
from drunk_snail.sources import StringSource



class fibonacci(Benchmark):

	def prepare(self, folding_depth):

		if not hasattr(self, 'templates'):

			self.templates = [
				Template(
					f't0',
					StringSource(f"<!-- (param)x -->")
				),
				Template(
					f't1',
					StringSource(f"<!-- (ref)t0 -->\n<!-- (param)x -->")
				)
			]

			for i in range(2, folding_depth):
				self.templates.append(
					Template(
						f't{i}',
						StringSource(f"<!-- (ref)t{i-2} -->\n<!-- (ref)t{i-1} -->\n<!-- (param)x -->")
					)
				)
		
		self.templates[-1]._actual_template._compiled = None
	
	def run(self, **kwargs):
		self.templates[-1].compiled


class fibonacci_with_function_compilation(Benchmark):

	def prepare(self, folding_depth):

		if not hasattr(self, 'templates'):

			self.templates = [
				Template(
					f't0', 
					StringSource(f"<!-- (param)x -->")
				),
				Template(
					f't1', 
					StringSource(f"<!-- (ref)t0 -->\n<!-- (param)x -->")
				)
			]

			for i in range(2, folding_depth):
				self.templates.append(
					Template(
						f't{i}', 
						StringSource(f"<!-- (ref)t{i-2} -->\n<!-- (ref)t{i-1} -->\n<!-- (param)x -->")
					)
				)
		
		self.templates[-1]._actual_template._function = None
	
	def run(self, **kwargs):
		self.templates[-1].function