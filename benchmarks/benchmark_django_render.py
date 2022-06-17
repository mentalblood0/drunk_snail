import django
import django.conf
import django.template
from sharpener import Benchmark



class table(Benchmark):

	def prepare(self, width, height):

		if not hasattr(self, 'table'):

			django.conf.settings.configure(TEMPLATES=[{
				'BACKEND': 'django.template.backends.django.DjangoTemplates'
			}])
			django.setup()

			self.table = django.template.Template(
				'<table>\n'
				'{% for row in table %}'
				'	<tr>'
				'{% for value in row %}\n'
				'		<td>{{ value }}</td>'
				'{% endfor %}\n'
				'	</tr>\n'
				'{% endfor %}'
				'</table>'
			)
			self.table_context = django.template.Context({
				'table': [
					[
						f"{x}.{y}"
						for x in range(width)
					]
					for y in range(height)
				]
			})
	
	def run(self, **kwargs):
		self.table.render(self.table_context)