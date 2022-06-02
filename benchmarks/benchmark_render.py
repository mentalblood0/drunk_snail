import json
from sharpener import Benchmark

from drunk_snail import Template
from drunk_snail.sources import FileSource



def generateFString(width, height):
	return ''.join([
		'<table>\n'
		''.join([
			''.join([
				'	<tr>\n',
				''.join([
					f'		<td>Table["Row"][{j}][{i}]</td>\n'
					for i in range(width)
				]),
				'	</tr>\n'
			])
			for j in range(height)
		]),
		'</table>'
	])


def getDimension(o: dict | list):
	return len(o['Row']), len(o['Row'][0]['cell'])
	return ''.join([
		f'{k}{getDimension(v)}'
		for k, v in o.items()
	] if type(o) == dict
	else [
		f'{getDimension(e)}'
		for e in o
	] if type(o) == list
	else ['_'])


class table_by_fstring(Benchmark):

	def prepare(self, width, height):

		if not hasattr(self, 'args'):
			self.fstring = generateFString(width, height)
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
		getDimension(self.args)
		self.fstring.format(Table=self.args)


class table(Benchmark):

	def prepare(self, width, height):

		if not hasattr(self, 'args'):

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


class args_to_str(Benchmark):

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
		str(self.args)


class args_to_json(Benchmark):

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
		json.dumps(self.args)


class args_to_json_with_indent(Benchmark):

	def prepare(self, width, height, **kwargs):

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
	
	def run(self, indent, **kwargs):
		json.dumps(self.args, indent=indent)


def render_append(Table):
	result = []
	result.append('<table>\n')
	for Row in Table['Row']:
		result.append('    <tr>\n')
		for cell in Row['cell']:
			result.append(f'''        <td>{cell}</td>\n''')
		result.append('    </tr>\n')
	result.append('</table>\n')
	return ''.join(result)


class table_by_append(Benchmark):

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
		render_append(self.args)


def render_comprehension(Table):
	return ''.join([
		'<table>\n',
		''.join([
			''.join([
				'    <tr>\n',
				''.join([
					f'        <td>{cell}</td>\n'
					for cell in Row['cell']
				]),
				'    </tr>\n'
			])
			for Row in Table['Row']
		]),
		'</table>\n'
	])


class table_by_comprehension(Benchmark):

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
		render_comprehension(self.args)


def render_comprehension_optimized(Table):
	return ''.join([
		'<table>\n',
		*[
			''.join([
				'    <tr>\n',
				*[
					f'        <td>{cell}</td>\n'
					for cell in Row['cell']
				],
				'    </tr>\n'
			])
			for Row in Table['Row']
		],
		'</table>\n'
	])


class table_by_comprehension_optimized(Benchmark):

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
		render_comprehension_optimized(self.args)


def renderRow(Row):
	return ''.join([
		'    <tr>\n',
		*[
			f'        <td>{cell}</td>\n'
			for cell in Row['cell']
		],
		'    </tr>\n'
	])


def render_comprehension_optimized_multifunction(Table):
	return ''.join([
		'<table>\n',
		*[
			renderRow(Row)
			for Row in Table['Row']
		],
		'</table>\n'
	])


class table_by_comprehension_optimized_multifunction(Benchmark):

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
		render_comprehension_optimized_multifunction(self.args)