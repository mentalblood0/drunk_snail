from . import setKeywords
from .keywords import default_keywords
from drunk_snail_c import compile as _compile
from drunk_snail_c import addTemplate as _addTemplate



def compileString(s, resulted_function_name='_temp', keywords=default_keywords, log=0):
	_addTemplate(resulted_function_name, s)
	setKeywords(resulted_function_name, keywords)
	return _compile(resulted_function_name, log)



import sys
sys.modules[__name__] = compileString