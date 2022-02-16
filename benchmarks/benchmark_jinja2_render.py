from jinja2 import Environment
from sharpener import Benchmark



class table(Benchmark):

	def prepare(self, width, height):

		if not hasattr(self, 'table'):

			self.env = Environment()
			self.table = self.env.from_string('<table>{% for row in rows %}<tr>{% for cell in row %}<td>{{ cell }}</td>{% endfor %}</tr>{% endfor %}</table>')

			self.args = {
				'rows':[
					[
						f"{x}.{y}"
						for x in range(width)
					]
					for y in range(height)
				]
			}
	
	def run(self, **kwargs):
		self.table.render(**self.args)