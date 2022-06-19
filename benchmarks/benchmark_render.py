import json
from sharpener import Benchmark

from drunk_snail import Template



class table(Benchmark):

	def prepare(self, width, height):

		if not hasattr(self, 'args'):

			with open('templates/Row.xml') as f:
				self.row = Template('Row', f.read())

			with open('templates/Table.xml') as f:
				self.table = Template('Table', f.read())

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