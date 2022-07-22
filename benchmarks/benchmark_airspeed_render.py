import airspeed
from sharpener_lite import Benchmark



class table(Benchmark):

	def prepare(self, width, height):

		if not hasattr(self, 'table'):

			self.table = airspeed.Template(
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
		self.table.merge(self.args)