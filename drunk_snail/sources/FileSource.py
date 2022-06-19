import pydantic

from ..Source import Source



class FileSource(Source):

	@pydantic.validate_arguments
	def __init__(self, path: str):
		self.path = path

	def get(self):
		with open(self.path) as f:
			return f.read()

	@property
	def id(self):
		return self.path