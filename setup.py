from distutils.core import setup, Extension
import os
import glob


if __name__ == '__main__':

	long_description = ''
	if os.path.exists('README.md'):
		with open('README.md') as f:
			long_description = f.read()

	setup(
		name='drunk_snail',
		version='1.4',
		description='Simple template engine. Faster than you think',
		long_description=long_description,
		long_description_content_type='text/markdown',
		author='mentalblood',
		author_email='neceporenkostepan@gmail.com',
		maintainer='mentalblood',
		maintainer_email='neceporenkostepan@gmail.com',
		keywords=['template', 'engine', 'fast'],
		url='https://github.com/MentalBlood/drunk_snail',
		packages=['drunk_snail'],
		ext_modules=[
			Extension(
				'compileTemplates',
				['drunk_snail/c/compileTemplates.c']
			)
		],
		data_files=glob.glob('drunk_snail/c/*')
	)