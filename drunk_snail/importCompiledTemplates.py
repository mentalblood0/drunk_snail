from .common import *

import os



def importCompiledTemplates(input_dir):

	result = {}

	for file_name in filter(lambda file_name: file_name.endswith('.py'), os.listdir(input_dir)):
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