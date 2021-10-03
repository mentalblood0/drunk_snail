from . import setKeywords
from .keywords import default_keywords
from drunk_snail_c import addTemplate as _addTemplate



def addTemplate(name, file_path, keywords={}):

	keywords = default_keywords | keywords
	
	with open(file_path) as f:
		template = f.read()
	
	_addTemplate(name, template)
	setKeywords(name, keywords)



import sys
sys.modules[__name__] = addTemplate