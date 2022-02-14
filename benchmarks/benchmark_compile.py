from sharpener import Benchmark

from drunk_snail import Template
from drunk_snail.sources import StringSource



class fibonacci(Benchmark):

	def prepare(self, keywords, folding_depth, template_name_prefix, approach):

		if not hasattr(self, 'templates'):

			self.templates = [
				Template(
					f'{template_name_prefix}0', 
					StringSource(f"{keywords['open_tag']} {keywords['param_operator']}x {keywords['close_tag']}"), 
					keywords,
					approach=approach
				),
				Template(
					f'{template_name_prefix}1', 
					StringSource(f"{keywords['open_tag']} {keywords['ref_operator']}{template_name_prefix}0 {keywords['close_tag']}\n{keywords['open_tag']} {keywords['param_operator']}x {keywords['close_tag']}"), 
					keywords,
					approach=approach
				)
			]

			for i in range(2, folding_depth):
				self.templates.append(
					Template(
						f'{template_name_prefix}{i}', 
						StringSource(f"{keywords['open_tag']} {keywords['ref_operator']}{template_name_prefix}{i-2} {keywords['close_tag']}\n{keywords['open_tag']} {keywords['ref_operator']}{template_name_prefix}{i-1} {keywords['close_tag']}\n{keywords['open_tag']} {keywords['param_operator']}x {keywords['close_tag']}"), 
						keywords,
						approach=approach
					)
				)
		
		self.templates[-1]._actual_template._compiled = None
	
	def run(self, **kwargs):
		self.templates[-1].compiled