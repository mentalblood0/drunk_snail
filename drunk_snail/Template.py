from __future__ import annotations

from threading import Lock
from typing import Callable
from types import ModuleType

import drunk_snail_c
from .Source import Source



templates: dict[str, _Template] = {}


class Template:

	def __init__(self, name: str, source: Source=None):

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
		
		if not self._actual_template_name in templates:
			raise KeyError(f"Template '{self._actual_template_name}' deleted or not created yet")
		
		return templates[self._actual_template_name]

	def __getattribute__(self, name: str):

		if name in ['_actual_template_name', '_actual_template', 'delete']:
			return super().__getattribute__(name)

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

	def __init__(self, name: str, source: Source):

		if not hasattr(self, '_lock'):
			self._lock = Lock()
		
		self._name = name
		self._source = source

		self._compiled = None
		self._function = None

		text = self.source.get()
		self._buffer_size = len(text) * 5 or 1
		
		drunk_snail_c.addTemplate(self.name, text)
		
		self.source.onChange = self.reload
	
	def reload(self, source: Source=None, checked: dict[str, bool]=None) -> int:

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
			self.__init__(
				self.name, 
				source or self.source
			)
		
		return reloaded_number
	
	@property
	def name(self) -> str:
		return self._name
	
	@property
	def source(self) -> Source:
		return self._source
	
	@property
	def text(self) -> str:
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
		return drunk_snail_c.getTemplateRefs(self.name)
	
	@property
	def function(self) -> Callable:

		if not self._function:
			compiled_function = compile(self.compiled, '', 'exec')
			temp_module = ModuleType('')
			exec(compiled_function, temp_module.__dict__)

			self._function = getattr(temp_module, 'render')
		
		return self._function
	
	def __call__(self, parameters: dict=None) -> str:
		return self.function(parameters or {})
	
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
