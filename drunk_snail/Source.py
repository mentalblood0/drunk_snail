from abc import ABCMeta, abstractmethod



class Source(metaclass=ABCMeta):

	@abstractmethod
	def get(self):
		pass
	
	@abstractmethod
	def id(self):
		pass
	
	@property
	def onChange(self):
		pass
	
	@onChange.setter
	def onChange(self, value):
		self.onChange_setter(value)

	@abstractmethod
	def onChange_setter(self, value):
		pass

	def __repr__(self):
		return f"({self.id})"



import sys
sys.modules[__name__] = Source