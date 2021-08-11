import os
from functools import cache

from .common import *



@cache
def getRenderer(input_dir, name):

	return getattr(
		importModuleFromPath(
			f'compiled_templates.{name}',
			os.path.join(input_dir, f'{name}.py')
		),
		'render'
	)



import sys
sys.modules[__name__] = getRenderer