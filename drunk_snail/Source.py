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
	
	def __hash__(self):
		return hash(f"{self.__class__.__name__}:{self.id}")