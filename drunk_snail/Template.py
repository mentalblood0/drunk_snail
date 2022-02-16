from __future__ import annotations

import re
import os
from threading import Lock
from types import ModuleType
from typing import Callable

import drunk_snail_c
from .Source import Source
from .sources import FileSource
from .syntax import default_keywords



templates: dict[str, _Template] = {}

keywords_symbols: dict[str, str] = {

	'open_tag': 'o',
	'close_tag': 'c',
	
	'param_operator': 'p',
	'ref_operator': 'r',
	'optional_operator': '?',
	
	'line_break': 'n'

}

approaches = {
	'comprehension': drunk_snail_c.compileComprehension,
	'append': drunk_snail_c.compileAppend
}


class Template:

	def __init__(self, name: str, source: Source=None, keywords: dict[str, str]=None, initial_buffer_size: int=None, approach: str='comprehension'):

		if not name in templates:
			templates[name] = _Template(
				name=name, 
				source=source, 
				keywords=keywords or default_keywords, 
				initial_buffer_size=initial_buffer_size,
				approach=approach
			)
		elif (
				source and 
				(source != templates[name].source)
			) or (
				keywords and 
				(keywords != templates[name].keywords)
			) or (
				approach and 
				(approach != templates[name].approach)
			):
			templates[name].reload(source=source, keywords=keywords, approach=approach)

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

	def __init__(self, name: str, source: Source, keywords: dict[str, str]=default_keywords, initial_buffer_size: int=None, approach=None):

		if not hasattr(self, '_lock'):
			self._lock = Lock()
		
		self._name = name
		self._source = source
		self._keywords = default_keywords | keywords
		self._approach = approach
		self._approachFunc = approaches[approach]

		self._compiled = None
		self._function = None

		text = self.source.get()
		self._buffer_size = initial_buffer_size or len(text) * 5 or 1
		
		drunk_snail_c.addTemplate(self.name, text)

		for type, keyword in self.keywords.items():
			
			if not type in default_keywords:
				raise Exception(f"No such keyword type: '{type}'")

			symbol = keywords_symbols[type]
			drunk_snail_c.removeKeyword(self.name, symbol)
			drunk_snail_c.addKeyword(self.name, keyword, symbol)
		
		self.source.onChange = self.reload
	
	def reload(self, source: Source=None, keywords: dict[str, str]=None, checked: dict[str, bool]=None, approach: str=None) -> int:

		checked = checked or {}
		reloaded_number = 1

		with self.lock:

			checked[self.name] = True

			for name in templates:
				if name not in checked:

					print('check', name)
				
					checked[name] = True
					
					t = templates[name]
					if self.name in t.refs:
						print(self.name, 'in', t)
						reloaded_number += t.reload(checked=checked)

			drunk_snail_c.removeTemplate(self.name)
			self.__init__(
				self.name, 
				source or self.source, 
				keywords or self.keywords,
				initial_buffer_size=self._buffer_size,
				approach=approach or self.approach
			)
		
		return reloaded_number
	
	@property
	def name(self) -> str:
		return self._name
	
	@property
	def source(self) -> Source:
		return self._source
	
	@property
	def keywords(self) -> dict[str, str]:
		return self._keywords
	
	@property
	def approach(self) -> str:
		return self._approach
	
	@property
	def text(self) -> str:
		return drunk_snail_c.getTemplate(self.name)
	
	@property
	def lock(self) -> Lock:
		return self._lock
	
	@property
	def compiled(self) -> str:

		with self.lock:
		
			if not self._compiled:
				
				while True:
					
					code, message, result = self._approachFunc(self.name, self._buffer_size)
					
					if code == 2:
						self._buffer_size *= 2
					
					elif code != 0:

						not_loaded_list = re.search(r'\"(.*)\": not loaded', message).groups()

						if len(not_loaded_list) and hasattr(self.source, 'path'):
							for name in not_loaded_list:
								p = self.source.path
								file_path = f"{os.path.dirname(p)}{os.path.sep}{name}{os.path.splitext(os.path.basename(p))[1]}"
								Template(name, FileSource(file_path))
						
						else:
							raise Exception(message)
					
					else:
						break
				
				self._compiled = result
		
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
		return f"(name='{self.name}', source={self.source}, keywords={self.keywords})"
	
	def __str__(self) -> str:
		return self.text
	
	def __len__(self) -> int:
		return len(self.text)

	def __eq__(self, other) -> bool:
		return (
			isinstance(other, self.__class__)
			and hash(self) == hash(other)
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
			'name', 'source', 'keywords', 'text', 'compiled', 
			'__call__', '__repr__', '__str__', '__len__', '__eq__', '__dir__', '__del__', '__hash__'
		]
