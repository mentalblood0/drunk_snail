import chevron
import functools
from sharpener_lite import Benchmark

from benchmarks.common import WithOutputMetrics, WithName



class table(Benchmark, WithOutputMetrics, WithName):

	name = 'chevron'
	link = 'https://github.com/noahmorrison/chevron'

	def prepare(self):
		self.table
		self.args

	@functools.cached_property
	def table(self):
		return (
			'<table>\n'
			'{{#Row}}\n'
			'    <tr>\n'
			'{{#cell}}\n'
			'        <td>{{value}}</td>\n'
			'{{/cell}}\n'
			'    </tr>\n'
			'{{/Row}}\n'
			'</table>\n'
		)

	@functools.cached_property
	def args(self):
		return {
			"Row": [
				{
					"cell": [
						{
							'value': str(x)
						}
						for x in range(self.config.kwargs['width'])
					]
				}
				for y in range(self.config.kwargs['height'])
			]
		}
	
	def run(self):
		return chevron.render(self.table, self.args)