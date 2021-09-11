from drunk_snail_c import compile as _compile



def compile(name, log=0):
	return _compile(name, log)



import sys
sys.modules[__name__] = compile