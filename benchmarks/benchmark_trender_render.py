from trender import TRender
from sharpener_lite import Benchmark



class table(Benchmark):

	def prepare(self, width, height):

		if not hasattr(self, 'table'):

			self.table = TRender(
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

			self.args = {
				'table': [
					[
						str(x)
						for x in range(width)
					]
					for y in range(height)
				]
			}
	
	def run(self, **kwargs):
		self.table.render(self.args)