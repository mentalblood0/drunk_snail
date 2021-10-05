from .. import Source



class StringSource(Source):

	def __init__(self, string):
		self.string = string
	
	def get(self):
		return self.string
	
	@property
	def id(self):
		return f"'{self.string}'"



import sys
sys.modules[__name__] = StringSource