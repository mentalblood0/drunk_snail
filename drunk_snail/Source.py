from abc import ABCMeta, abstractmethod



class Source(metaclass=ABCMeta):

	@abstractmethod
	def get(self):
		pass



import sys
sys.modules[__name__] = Source