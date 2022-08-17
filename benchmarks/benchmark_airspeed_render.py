import airspeed
import functools
from sharpener_lite import Benchmark

from benchmarks.common import WithOutputMetrics, WithName



class table(Benchmark, WithOutputMetrics, WithName):

	name = 'airspeed'
	link = 'https://github.com/purcell/airspeed'

	def prepare(self):
		self.table
		self.args

	@functools.cached_property
	def table(self):
		return airspeed.Template(
			'<table>\n'
			'#foreach ($row in $table)'
			'	<tr>\n'
			'#foreach ($value in $row)'
			'		<td>$value</td>\n'
			'#end'
			'	</tr>\n'
			'#end'
			'</table>'
		)

	@functools.cached_property
	def args(self):
		return {
			'table': [
				[
					str(x)
					for x in range(self.config.kwargs['width'])
				]
				for y in range(self.config.kwargs['height'])
			]
		}
	
	def run(self):
		return self.table.merge(self.args)