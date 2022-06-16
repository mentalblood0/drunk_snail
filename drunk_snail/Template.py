from __future__ import annotations

import pydantic

import drunk_snail_c
from typing import Any
from .Source import Source



templates: dict[str, _Template] = {}


def replaceValuesByPaths(o: dict | list | Any, prefix: str):
	if type(o) == dict:
		return {
			k: replaceValuesByPaths(v, f'{prefix}["{k}"]')
			for k, v in o.items()
		}
	elif type(o) == list:
		return [
			replaceValuesByPaths(e, f'{prefix}[{i}]')
			for i, e in enumerate(o)
		]
	else:
		return f'{{{prefix}}}'


class Template:

	@pydantic.validate_arguments(config={'arbitrary_types_allowed': True})
	def __init__(self, name: str, source: Source | None = None):

		if not name in templates:
			templates[name] = _Template(
				name=name, 
				source=source
			)
		elif (
				source and 
				(source != templates[name].source)
			):
			templates[name].reload(source=source)

		self._actual_template_name = name
	
	@property
	def _actual_template(self) -> _Template:

		try:
			result = templates[self._actual_template_name]
		except KeyError:
			raise KeyError(f"Template '{self._actual_template_name}' deleted or not created yet")
		
		return result

	def __getattribute__(self, name: str):

		if name in ['_actual_template_name', '_actual_template', 'delete']:
			return super().__getattribute__(name)
		else:
			return getattr(self._actual_template, name)

	def __call__(self, *args, **kwargs):
		return self._actual_template(*args, **kwargs)

	def __repr__(self):
		return self._actual_template.__repr__()

	def __str__(self):
		return self._actual_template.__str__()

	def __len__(self):
		return self._actual_template.__len__()

	def __eq__(self, other):
		return self._actual_template.__eq__(other)

	def __dir__(self):
		return self._actual_template.__dir__()

	def __hash__(self):
		return self._actual_template.__hash__()

	def delete(self):
		try:
			self._actual_template.__del__()
		except KeyError:
			pass


class _Template:

	@pydantic.validate_arguments(config={'arbitrary_types_allowed': True})
	def __init__(self, name: str, source: Source):

		self._name = name
		self._source = source

		text = self.source.get()
		self._buffer_size = len(text) * 5 or 1

		drunk_snail_c.addTemplate(self.name, text)

		self.source.onChange = self.reload

	@pydantic.validate_arguments(config={'arbitrary_types_allowed': True})
	def reload(self, source: Source = None) -> None:
		drunk_snail_c.removeTemplate(self.name)
		drunk_snail_c.addTemplate(self.name, (source or self.source).get())

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

	def __del__(self) -> None:

		there_was_template = drunk_snail_c.removeTemplate(self.name)

		if there_was_template:

			if self.name in templates:
				del templates[self.name]

			self.source.clean()

	def __hash__(self) -> int:
		return hash(self.source)

	def __dir__(self) -> list[str]:
		return [
			'name', 'source', 'text', 
			'__call__', '__repr__', '__str__', '__len__', '__eq__', '__dir__', '__del__', '__hash__'
		]
