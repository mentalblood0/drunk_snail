from __future__ import annotations

import pydantic
from threading import Lock
from typing import Callable
from types import ModuleType

import drunk_snail_c
from typing import Any
from .Cache import Cache
from .Source import Source
from .compilePythonFunction import compilePythonFunction



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

		if not hasattr(self, '_lock'):
			self._lock = Lock()

		self._name = name
		self._source = source

		self._compiled = None
		self._function = None
		self._cache = None

		text = self.source.get()
		self._buffer_size = len(text) * 5 or 1

		with self.lock:
			drunk_snail_c.addTemplate(self.name, text)

		self.source.onChange = self.reload

	@pydantic.validate_arguments(config={'arbitrary_types_allowed': True})
	def reload(self, source: Source | None = None, checked: dict[str, bool] | None = None) -> int:

		checked = checked or {}
		reloaded_number = 1

		with self.lock:

			checked[self.name] = True

			for name in templates:
				if name not in checked:
				
					checked[name] = True
					
					t = templates[name]
					if self.name in t.refs:
						reloaded_number += t.reload(checked=checked)

			drunk_snail_c.removeTemplate(self.name)

		self.__init__(self.name, source or self.source)

		return reloaded_number

	@property
	def name(self) -> str:
		return self._name

	@property
	def source(self) -> Source:
		return self._source

	@property
	def text(self) -> str:
		with self.lock:
			return drunk_snail_c.getTemplate(self.name)

	@property
	def lock(self) -> Lock:
		return self._lock

	@property
	def compiled(self) -> str:

		if not self._compiled:
			with self.lock:
				self._compiled, self._buffer_size = drunk_snail_c.compile(self.name, self._buffer_size)
		
		return self._compiled

	@property
	def refs(self) -> list[str]:
		with self.lock:
			return drunk_snail_c.getTemplateRefs(self.name)

	@property
	def function(self) -> Callable[[dict], str]:

		if not self._function:
			self._function = compilePythonFunction(self.compiled, 'render')

		return self._function

	def composeFstring(self, parameters) -> str:
		return self(replaceValuesByPaths(parameters, self.name))

	def setupCache(self, paths: set[tuple[str]]):
		with self.lock:
			self._cache = Cache(paths)

	def __call__(
		self,
		parameters: dict = None,
		use_cache: bool = False
	) -> str:

		parameters = parameters or {}

		if use_cache:

			if not self._cache:
				raise Exception(f'Use .setupCache before')

			try:
				return self._cache.get(parameters)(parameters)
			except KeyError:
				return self._cache.set(
					template_name=self.name,
					parameters=parameters,
					fstring=self.composeFstring(parameters)
				)(parameters)

		return self.function(parameters)

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
	
		with self.lock:

			there_was_template = drunk_snail_c.removeTemplate(self.name)

			if there_was_template:

				if self.name in templates:
					del templates[self.name]

				self.source.clean()

	def __hash__(self) -> int:
		return hash(self.source)

	def __dir__(self) -> list[str]:
		return [
			'name', 'source', 'text', 'compiled', 
			'__call__', '__repr__', '__str__', '__len__', '__eq__', '__dir__', '__del__', '__hash__'
		]
