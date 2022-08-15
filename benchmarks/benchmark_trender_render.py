import functools
from trender import TRender
from sharpener_lite import Benchmark

from benchmarks.common import WithOutputMetrics



class table(Benchmark, WithOutputMetrics):

	def prepare(self):
		self.table
		self.args

	@functools.cached_property
	def args(self):
		return {
			'table': [
				[
					str(x)
					for x in range(self.config.kwargs['height'])
				]
				for y in range(self.config.kwargs['width'])
			]
		}

	@functools.cached_property
	def table(self):
		return TRender(
			'<table>\n'
			'#for @row in @table:\n'
			'	<tr>\n'
			'#for @value in @row:\n'
			'		<td>@value</td>\n'
			'#end\n'
			'	</tr>\n'
			'#end\n'
			'</table>'
		)

	def run(self):
		return self.table.render(self.args)