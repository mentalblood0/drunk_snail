import json
import orjson
import functools
from sharpener_lite import Benchmark

from drunk_snail import Template
from drunk_snail_python import render_hardcoded
from benchmarks.common import WithOutputMetrics, WithTableArgs, WithName



class table_hardcoded(Benchmark, WithOutputMetrics, WithTableArgs, WithName):

	name = 'hardcoded'
	link = None

	def prepare(self):
		self.args

	@functools.cached_property
	def args(self):
		return {
			"Row": [
				{
					"cell": [
						str(x + y * self.config.kwargs['width'])
						for x in range(self.config.kwargs['width'])
					]
				}
				for y in range(self.config.kwargs['height'])
			]
		}

	def run(self):
		return render_hardcoded(self.args)


class table_multiparam(Benchmark, WithOutputMetrics, WithName):

	name = 'multiparam'
	link = None

	def prepare(self):
		self.cells
		self.row_multiparam
		self.table_multiparam
		self.args

	def registerFromFile(self, name: str):
		result = Template(name)
		with open(f'templates/{name}.xml') as f:
			result.register(f.read())
		return result

	@functools.cached_property
	def cells(self):
		return self.registerFromFile('cells')

	@functools.cached_property
	def row_multiparam(self):
		return self.registerFromFile('RowMultiparam')

	@functools.cached_property
	def table_multiparam(self):
		return self.registerFromFile('TableMultiparam')

	@functools.cached_property
	def args(self):
		return {
			"RowMultiparam": [
				{
					"cells": [
						{
							'a': str(4*x),
							'b': str(4*x + 1),
							'c': str(4*x + 2),
							'd': str(4*x + 3)
						}
						for x in range(self.config.kwargs['width'])
					]
				}
				for y in range(self.config.kwargs['height'])
			]
		}

	def run(self):
		return self.table_multiparam(self.args)


class args_to_str(Benchmark, WithOutputMetrics, WithTableArgs, WithName):
	name = 'Arguments to string'
	link = None
	def run(self):
		return str(self.args)


class args_to_json(Benchmark, WithOutputMetrics, WithTableArgs, WithName):
	name = 'Arguments to JSON'
	link = None
	def run(self):
		return json.dumps(self.args)


class args_to_json_using_orjson(Benchmark, WithOutputMetrics, WithTableArgs, WithName):
	name = 'Arguments to JSON using orjson'
	link = 'https://github.com/ijl/orjson'
	def run(self):
		return orjson.dumps(self.args)


class args_to_json_with_indent(Benchmark, WithOutputMetrics, WithTableArgs):
	name = 'Arguments to json with indent'
	link = None
	def run(self):
		return json.dumps(self.args, indent=self.config.kwargs['indent'])