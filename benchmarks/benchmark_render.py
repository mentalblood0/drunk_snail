from sharpener import Benchmark

from drunk_snail import Template
from drunk_snail.sources import FileSource



class table(Benchmark):

	def prepare(self, width, height):

		self.row = Template('Row', FileSource('templates/Row.xml'))
		self.table = Template('Table', FileSource('templates/Table.xml'))

		if not hasattr(self, 'args'):
			self.args = {
				"Row": [
					{
						"cell": [
							f"{x}.{y}"
							for x in range(width)
						]
					}
					for y in range(height)
				]
			}
	
	def run(self, **kwargs):
		self.table(self.args)
	
	def clean(self, **kwargs):
		self.row.delete()
		self.table.delete()


def render(Table):
	result = []
	result.append('<table>\n')
	for Row in Table['Row']:
		result.append('    <tr>\n')
		for cell in Row['cell']:
			result.append(f'''        <td>{cell}</td>\n''')
		result.append('    </tr>\n')
	result.append('</table>')
	return ''.join(result)


class table_by_func(Benchmark):

	def prepare(self, width, height):

		if not hasattr(self, 'args'):
			self.args = {
				"Row": [
					{
						"cell": [
							f"{x}.{y}"
							for x in range(width)
						]
					}
					for y in range(height)
				]
			}
	
	def run(self, **kwargs):
		render(self.args)