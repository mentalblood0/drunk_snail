import os
import glob
from setuptools import setup, Extension
# from distutils.core import setup, Extension



if __name__ == '__main__':

	long_description = ''
	if os.path.exists('README.md'):
		with open('README.md') as f:
			long_description = f.read()
	
	data_files = {}
	for p in glob.glob('drunk_snail/c/*.c') + glob.glob('drunk_snail/c/**/*.c', recursive=True):
		dirname = os.path.dirname(p)
		if dirname not in data_files:
			data_files[dirname] = []
		data_files[dirname].append(p)

	setup(
		name='drunk_snail',
		version='5.2.0',
		description='Simple template engine. Faster than you think',
		long_description=long_description,
		long_description_content_type='text/markdown',
		author='mentalblood',
		author_email='neceporenkostepan@gmail.com',
		maintainer='mentalblood',
		maintainer_email='neceporenkostepan@gmail.com',
		keywords=['template', 'engine', 'fast'],
		url='https://github.com/MentalBlood/drunk_snail',
		packages=['drunk_snail', 'drunk_snail.sources'],
		ext_modules=[
			Extension(
				'drunk_snail_c',
				['drunk_snail/c/drunk_snail_c.c'],
				extra_compile_args=['-O3']
			)
		],
		install_requires=[
			'watchdog'
		],
		data_files=list(data_files.items())
	)