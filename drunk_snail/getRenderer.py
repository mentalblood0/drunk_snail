import os
from functools import cache

from .common import *



@cache
def _getRenderer(input_dir, name, last_modified_time):

	return getattr(
		importModuleFromPath(
			f'drunk_snail.renderers.{name}',
			os.path.join(input_dir, f'{name}.py')
		),
		'render'
	)


def getRenderer(input_dir, name):

	file_path = os.path.join(input_dir, f'{name}.py')

	return _getRenderer(input_dir, name, os.path.getmtime(file_path))



import sys
sys.modules[__name__] = getRenderer