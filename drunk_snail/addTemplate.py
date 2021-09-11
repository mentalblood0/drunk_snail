from drunk_snail_c import addTemplate as _addTemplate



def addTemplate(name, file_path):
	
	with open(file_path) as f:
		template = f.read()
	
	return _addTemplate(name, template)



import sys
sys.modules[__name__] = addTemplate