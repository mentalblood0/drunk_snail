import json
import orjson
from sharpener_lite import Benchmark

from drunk_snail import Template



class table(Benchmark):

	def prepare(self, width, height):

		if not hasattr(self, 'args'):

			self.row = Template('Row')
			with open('templates/Row.xml') as f:
				self.row.register(f.read())

			self.table = Template('Table')
			with open('templates/Table.xml') as f:
				self.table.register(f.read())

			self.args = {
				"Row": [
					{
						"cell": [
							str(x)
							for x in range(width)
						]
					}
					for y in range(height)
				]
			}

	def run(self, **kwargs):
		self.table(self.args)


class table_multiparam(Benchmark):

	def prepare(self, width, height):

		if not hasattr(self, 'args'):

			with open('templates/cells.xml') as f:
				Template('cells').register(f.read())

			with open('templates/RowMultiparam.xml') as f:
				Template('RowMultiparam').register(f.read())

			self.table = Template('TableMultiparam')
			with open('templates/TableMultiparam.xml') as f:
				self.table_text = f.read()
			self.table.register(self.table_text)

			self.args = {
				"RowMultiparam": [
					{
						"cells": [
							{
								'a': str(4*x),
								'b': str(4*x + 1),
								'c': str(4*x + 2),
								'd': str(4*x + 3)
							}
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
							str(x)
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
							str(x)
							for x in range(width)
						]
					}
					for y in range(height)
				]
			}
	
	def run(self, **kwargs):
		json.dumps(self.args)


class args_to_json_using_orjson(Benchmark):

	def prepare(self, width, height):

		if not hasattr(self, 'args'):
			self.args = {
				"Row": [
					{
						"cell": [
							str(x)
							for x in range(width)
						]
					}
					for y in range(height)
				]
			}
	
	def run(self, **kwargs):
		orjson.dumps(self.args)


class args_to_json_with_indent(Benchmark):

	def prepare(self, width, height, **kwargs):

		if not hasattr(self, 'args'):
			self.args = {
				"Row": [
					{
						"cell": [
							str(x)
							for x in range(width)
						]
					}
					for y in range(height)
				]
			}
	
	def run(self, indent, **kwargs):
		json.dumps(self.args, indent=indent)