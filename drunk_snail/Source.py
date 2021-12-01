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

	def onChange_setter(self, value):
		pass
	
	def clean(self):
		pass

	def __repr__(self):
		return f"({self.id})"
	
	def __hash__(self):
		return hash(f"{self.__class__.__name__}:{self.id}")



import sys
sys.modules[__name__] = Source