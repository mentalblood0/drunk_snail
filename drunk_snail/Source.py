from abc import ABCMeta, abstractmethod



class Source(metaclass=ABCMeta):

	@abstractmethod
	def get(self):
		pass
	
	@abstractmethod
	def id(self):
		pass

	def __repr__(self):
		return f"({self.id})"



import sys
sys.modules[__name__] = Source