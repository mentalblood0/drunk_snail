from sharpener import Benchmark

from drunk_snail import Template
from drunk_snail.sources import FileSource



class table(Benchmark):

	def prepare(self, width, height):

		self.row = Template('Row', FileSource('templates/Row.xml'))
		self.table = Template('Table', FileSource('templates/Table.xml'))

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