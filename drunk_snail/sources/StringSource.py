import pydantic
from ..Source import Source



class StringSource(Source):

	@pydantic.validate_arguments
	def __init__(self, string: str):
		self.string = string

	def get(self):
		return self.string

	@property
	def id(self):
		return f"'{self.string}'"