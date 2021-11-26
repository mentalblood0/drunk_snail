import os

from .common import *



def importCompiledTemplates(input_dir, templates_to_import=None):

	result = {}

	if templates_to_import != None:
		files_names = map(lambda name: f'{name}.py', templates_to_import)
	else:
		files_names = filter(lambda file_name: file_name.endswith('.py'), os.listdir(input_dir))

	for file_name in files_names:
		module_name = file_name.split('.')[0]
		result[module_name] = getattr(
			importModuleFromPath(
				f'compiled_templates.{module_name}',
				os.path.join(input_dir, file_name)
			),
			'render'
		)

	return result



import sys
sys.modules[__name__] = importCompiledTemplates