import dataclasses
from typing import Callable
from functools import reduce

from .compilePythonFunction import compilePythonFunction



@dataclasses.dataclass(frozen=True)
class Cache:

	paths: set[tuple[str]]
	values: dict[str, Callable[[dict], str]] = dataclasses.field(default_factory=dict)

	def _composeKey(self, parameters: dict):
		return '_'.join(
			str(len(
				reduce(
					lambda v, k: v[k],
					p,
					parameters
				)
			))
			for p in self.paths
		)

	def _composeValue(self, template_name: str, fstring: str):
		return compilePythonFunction(
			f'render = lambda {template_name}: f\'\'\'{fstring}\'\'\'',
			'render'
		)

	def set(self, template_name: str, parameters: dict, fstring: str):

		value = self._composeValue(template_name, fstring)
		self.values[self._composeKey(parameters)] = value

		return value

	def get(self, parameters: dict):
		return self.values[self._composeKey(parameters)]