from drunk_snail_c import addTemplate as _addTemplate
from drunk_snail_c import compile as _compile



def compileString(s, resulted_function_name='_temp', log=0):
	_addTemplate(resulted_function_name, s)
	return _compile(resulted_function_name, log)



import sys
sys.modules[__name__] = compileString