import glob
from setuptools import setup, Extension, find_packages



if __name__ == '__main__':

	setup(

		name='drunk_snail',
		version='7.1.1',
		python_requires='>=3.5',
		keywords=['template-engine', 'ragel'],
		url='https://github.com/MentalBlood/drunk_snail',

		description='Template engine. Faster than you think',
		long_description=open('README.md').read(),
		long_description_content_type='text/markdown',

		classifiers=[
			'Development Status :: 5 - Production/Stable',
			'Intended Audience :: Developers',
			'Topic :: Internet :: WWW/HTTP :: Dynamic Content',
			'Topic :: Text Processing :: Markup :: XML',
			'Topic :: Text Processing :: Markup :: HTML',
			'Typing :: Typed',
			'Operating System :: OS Independent',
			'Programming Language :: C',
			'Programming Language :: Python :: 3.5',
			'License :: OSI Approved :: BSD License'
		],

		author='mentalblood',
		author_email='neceporenkostepan@gmail.com',
		maintainer='mentalblood',
		maintainer_email='neceporenkostepan@gmail.com',

		packages=find_packages(exclude=['tests']),
		ext_modules=[
			Extension(
				name='drunk_snail_python',
				sources=glob.glob(f'drunk_snail/drunk_snail_python/**/*.c', recursive=True),
				extra_compile_args=['-O3']
			)
		]

	)
