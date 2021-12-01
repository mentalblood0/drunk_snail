from threading import Lock
from types import ModuleType

import drunk_snail_c
from . import templates, syntax, default_keywords



def Template(name, *args, **kwargs):

	if not name in templates:
		templates[name] = _Template(name, *args, **kwargs)
	else:
		if args or kwargs:
			templates[name].reload(*args, **kwargs)

	return _Template_proxy(name)


class _Template_proxy:

	def __init__(self, name):
		self._actual_template_name = name
	
	@property
	def _actual_template(self):
		
		if not self._actual_template_name in templates:
			raise KeyError(f"Template '{self._actual_template_name}' not exists (seems to be deleted)")
		
		return templates[self._actual_template_name]

	def __getattribute__(self, name):

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
	
	def delete(self):
		try:
			self._actual_template.__del__()
		except KeyError:
			pass


class _Template:

	def __init__(self, name, source, keywords=default_keywords, initial_buffer_size=None):

		if not hasattr(self, '_lock'):
			self._lock = Lock()
		
		self._name = name
		self._source = source
		self._keywords = default_keywords | keywords

		self._compiled = None
		self._function = None

		text = self.source.get()
		self._buffer_size = initial_buffer_size or len(text) * 5 or 1
		
		drunk_snail_c.addTemplate(self.name, text)

		for type, keyword in self.keywords.items():
			
			if not type in syntax:
				return False

			old_value = syntax[type].value
			syntax[type].value = keyword

			drunk_snail_c.removeKeyword(self.name, old_value)
			drunk_snail_c.addKeyword(self.name, syntax[type].value, syntax[type].symbol)
		
		self.source.onChange = self.reload
	
	def reload(self, source=None, keywords=None, _not_reload=None):

		_not_reload = _not_reload or {}

		reloaded_number = 1

		with self._lock:

			_not_reload[self.name] = True

			for name in filter(lambda t: t not in _not_reload, templates):
				
				_not_reload[name] = True
				
				t = templates[name]
				if self.name in t.refs:
					reloaded_number += t.reload(_not_reload=_not_reload)

			drunk_snail_c.removeTemplate(self.name)
			self.__init__(
				self.name, 
				source or self.source, 
				keywords or self.keywords,
				self._buffer_size
			)
		
		return reloaded_number
	
	@property
	def name(self):
		return self._name
	
	@property
	def source(self):
		return self._source
	
	@property
	def keywords(self):
		return self._keywords
	
	@property
	def text(self):
		return drunk_snail_c.getTemplate(self.name)
	
	@property
	def compiled(self):

		with self._lock:
		
			if not self._compiled:
				
				while True:
					code, message, result = drunk_snail_c.compile(self.name, self._buffer_size, 0)
					if code == 2:
						self._buffer_size *= 2
					elif code != 0:
						raise Exception(message)
					else:
						break
				
				self._compiled = result
		
		return self._compiled
	
	@property
	def refs(self):
		return drunk_snail_c.getTemplateRefs(self.name)
	
	def __call__(self, parameters={}):

		if not self._function:
			compiled_function = compile(self.compiled, '', 'exec')
			temp_module = ModuleType('')
			exec(compiled_function, temp_module.__dict__)

			self._function = getattr(temp_module, 'render')

		return self._function(parameters)
	
	def __repr__(self):
		return f"(name='{self.name}', source={self.source}, keywords={self.keywords})"
	
	def __str__(self):
		return self.text
	
	def __len__(self):
		return len(self.text)

	def __eq__(self, other):
		return (
			isinstance(other, self.__class__)
			and str(other) == str(self)
		)
	
	def __del__(self):
	
		with self._lock:

			there_was_template = drunk_snail_c.removeTemplate(self.name)

			if there_was_template:

				if self.name in templates:
					del templates[self.name]

				self.source.clean()

	def __dir__(self):
		return [
			'name', 'source', 'keywords', 'text', 'compiled', 
			'__call__', '__repr__', '__str__', '__len__', '__eq__', '__dir__', '__del__'
		]



import sys
sys.modules[__name__] = Template
