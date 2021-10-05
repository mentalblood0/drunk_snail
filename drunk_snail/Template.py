from types import ModuleType

import drunk_snail_c
from . import templates, syntax, default_keywords



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

		drunk_snail_c.addTemplate(
			self.name, 
			self.source.get()
		)
		self.setKeywords(self.keywords)
	
	def reload(self, source=None, keywords=None):

		drunk_snail_c.removeTemplate(self.name)
		
		self.__init__(
			self.name, 
			source or self.source, 
			keywords or self.keywords
		)
	
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

		if self._compiled == None:
			self._compiled = drunk_snail_c.compile(self.name, 0)
		
		return self._compiled
	
	def setKeywords(self, keywords):

		for type, keyword in keywords.items():
			
			if not type in syntax:
				return False

			old_value = syntax[type].value
			syntax[type].value = keyword

			drunk_snail_c.removeKeyword(self.name, old_value)
			drunk_snail_c.addKeyword(self.name, syntax[type].value, syntax[type].symbol)
	
	def __call__(self, parameters):

		if not self._function:
			
			compiled_function = compile(self.compiled, '', 'exec')
			temp_module = ModuleType('temp_module')
			exec(compiled_function, temp_module.__dict__)

			self._function = getattr(temp_module, 'render')
		
		return self._function(parameters)
	
	def __repr__(self):
		return f"(name='{self.name}', source={self.source}, keywords={self.keywords})"



import sys
sys.modules[__name__] = Template
