import os
import glob
from setuptools import setup, Extension, find_packages



if __name__ == '__main__':

	long_description = ''
	if os.path.exists('README.md'):
		with open('README.md') as f:
			long_description = f.read()

	setup(
		name='drunk_snail',
		version='6.8.2',
		description='Simple template engine. Faster than you think',
		long_description=long_description,
		long_description_content_type='text/markdown',
		author='mentalblood',
		author_email='neceporenkostepan@gmail.com',
		maintainer='mentalblood',
		maintainer_email='neceporenkostepan@gmail.com',
		keywords=['template', 'engine', 'fast'],
		url='https://github.com/MentalBlood/drunk_snail',
		packages=find_packages(),
		ext_modules=[
			Extension(
				name='drunk_snail_c',
				sources=glob.glob('drunk_snail/c/*.c'),
				extra_compile_args=['/O2']
			)
		],
		install_requires=[],
		data_files=glob.glob('drunk_snail/c/*.c') + glob.glob('drunk_snail/c/*.h')
	)