import drunk_snail_c
from .keywords import *



class Template:

	def __init__(self, name, file_path, keywords=default_keywords):
		
		self._name = name
		self._file_path = file_path
		self._keywords = default_keywords | keywords

		self._text = None
		self._compiled = None
	
	@property
	def name(self):
		return self._name
	
	@property
	def file_path(self):
		return self._file_path
	
	@property
	def keywords(self):
		return self._keywords
	
	@property
	def text(self):

		if self._text == None:
			self.load()
		
		return self._text
	
	def load(self):

		with open(self.file_path) as f:
			self._text = f.read()
	
		drunk_snail_c.addTemplate(self.name, self._text)
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



import sys
sys.modules[__name__] = Template