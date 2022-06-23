import os
import glob
from setuptools import setup, Extension, find_packages



def paths(root: str, extension: str):
	return glob.glob(f'{root}/*.{extension}') + glob.glob(f'{root}/**/*.{extension}', recursive=True)


if __name__ == '__main__':

	long_description = ''
	if os.path.exists('README.md'):
		with open('README.md') as f:
			long_description = f.read()

	setup(
		name='drunk_snail',
		version='6.12.0',
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
				sources=paths('drunk_snail/drunk_snail_c', 'c'),
				extra_compile_args=['/O2']
			)
		],
		install_requires=[
			'pydantic'
		],
		data_files=paths('drunk_snail/drunk_snail_c', 'c') + paths('drunk_snail/drunk_snail_c', 'h')
	)