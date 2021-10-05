from functools import cached_property

from . import syntax
from .common import singleton



@singleton
class default_keywords:

	@cached_property
	def default_keywords(self):
		return {
			name: keyword.value
			for name, keyword in syntax.items()
		}



import sys
sys.modules[__name__] = default_keywords.default_keywords