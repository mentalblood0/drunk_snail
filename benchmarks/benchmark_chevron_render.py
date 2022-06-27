import chevron
from sharpener import Benchmark



class table(Benchmark):

	def prepare(self, width, height):

		if not hasattr(self, 'table'):

			self.table = (
				'<table>\n'
				'{{#Row}}\n'
				'	<tr>\n'
				'{{#cell}}\n'
				'		<td>{{value}}</td>\n'
				'{{/cell}}\n'
				'	</tr>\n'
				'{{/Row}}\n'
				'</table>'
			)

			self.args = {
				"Row": [
					{
						"cell": [
							{
								'value': str(x)
							}
							for x in range(width)
						]
					}
					for y in range(height)
				]
			}
	
	def run(self, **kwargs):
		chevron.render(self.table, self.args)