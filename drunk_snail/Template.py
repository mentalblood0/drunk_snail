from __future__ import annotations

import pydantic

import drunk_snail_c
from .Source import Source



templates: dict[str, Template] = {}


class Template:

	def __new__(_, name: str, source: Source = None):

		if name not in templates:
			templates[name] = _Template(name, source)

		result = templates[name]
		if source is not None:
			result.reload(source)

		return result


class _Template:

	@pydantic.validate_arguments(config={'arbitrary_types_allowed': True})
	def __init__(self, name: str, source: Source):

		self._name = name
		self._source = source
		self._buffer_size = 1

		self.reload(source)

	@pydantic.validate_arguments(config={'arbitrary_types_allowed': True})
	def reload(self, source: Source = None) -> None:

		if source != self.source:
			self._source = source

		print(f'reload {self.name} from {source} == {self.source.get()}')

		drunk_snail_c.removeTemplate(self.name)

		text = self.source.get()
		self._buffer_size = len(text)
		drunk_snail_c.addTemplate(self.name, text)

	@property
	def name(self) -> str:
		return self._name

	@property
	def source(self) -> Source:
		return self._source

	@property
	def text(self) -> str:
		return drunk_snail_c.getTemplate(self.name)

	def __call__(self, parameters: dict = None) -> str:
		result, self._buffer_size = drunk_snail_c.render(self.name, self._buffer_size, parameters or {})
		return result

	def __repr__(self) -> str:
		return f"(name='{self.name}', source={self.source})"
	
	def __str__(self) -> str:
		return self.text

	def __len__(self) -> int:
		return len(self.text)

	def __eq__(self, other) -> bool:
		return (
			isinstance(other, self.__class__)
			and (hash(self) == hash(other))
		)

	def __hash__(self) -> int:
		return hash(self.source)

	def __dir__(self) -> list[str]:
		return [
			'name', 'source', 'text', 
			'__call__', '__repr__', '__str__', '__len__', '__eq__', '__dir__', '__del__', '__hash__'
		]
