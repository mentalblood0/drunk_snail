from types import ModuleType

import drunk_snail_c
from .keywords import *
from . import templates



def Template(name, *args, **kwargs):

	if not name in templates:
		templates[name] = _Template(name, *args, **kwargs)

	return templates[name]


class _Template:

	def __init__(self, name, source, keywords=default_keywords):
		
		self._name = name
		self._source = source
		self._keywords = default_keywords | keywords

		self._compiled = None
		self._function = None

		self.load()
	
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

		result = drunk_snail_c.getTemplate(self.name)
		if result == None:
			self.load()
			result = drunk_snail_c.getTemplate(self.name)
		
		return result
	
	@property
	def function(self):

		assert self.compiled != None

		if not self._function:
			compiled_function = compile(self._compiled, '', 'exec')
			temp_module = ModuleType('temp_module')
			exec(compiled_function, temp_module.__dict__)

			self._function = getattr(temp_module, 'render')
		
		return self._function
	
	def load(self):
	
		drunk_snail_c.addTemplate(
			self.name, 
			self.source.get()
		)
		self.setKeywords(self.keywords)
	
	@property
	def compiled(self):

		if self._compiled == None:
			self.compile()
		
		return self._compiled

	def compile(self):

		assert self.text != None
		
		self._compiled = drunk_snail_c.compile(self.name, 0)

	def _setKeyword(self, template_name, type, keyword):

		if not type in syntax:
			return False

		old_value = syntax[type].value
		syntax[type].value = keyword

		drunk_snail_c.removeKeyword(template_name, old_value)
		drunk_snail_c.addKeyword(template_name, syntax[type].value, syntax[type].symbol)

		return True
	
	def setKeywords(self, keywords):

		for type_, keyword in keywords.items():
			self._setKeyword(self.name, type_, keyword)
	
	def __call__(self, parameters):
		return self.function(parameters)
	
	def __repr__(self):
		return f"(name='{self.name}', source={self.source}, keywords={self.keywords})"



import sys
sys.modules[__name__] = Template
