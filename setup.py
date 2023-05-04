import pathlib
import setuptools



if __name__ == '__main__':

	packages = setuptools.find_packages(exclude = ['tests'])

	setuptools.setup(

		name                          = 'drunk_snail',
		version                       = '7.2.7',
		python_requires               = '>=3.5',
		keywords                      = ['template-engine', 'ragel', 'fast'],
		url                           = 'https://github.com/MentalBlood/drunk_snail',

		description                   = 'Template engine. Faster than you think',
		long_description              = (pathlib.Path(__file__).parent / 'README.md').read_text(),
		long_description_content_type = 'text/markdown',

		classifiers                   = [
			'Development Status :: 5 - Production/Stable',
			'Intended Audience :: Developers',
			'Topic :: Internet :: WWW/HTTP :: Dynamic Content',
			'Topic :: Text Processing :: Markup :: XML',
			'Topic :: Text Processing :: Markup :: HTML',
			'Typing :: Typed',
			'Operating System :: OS Independent',
			'Programming Language :: C',
			'Programming Language :: Python :: 3.5',
			'Programming Language :: Python :: 3.6',
			'Programming Language :: Python :: 3.7',
			'Programming Language :: Python :: 3.8',
			'Programming Language :: Python :: 3.9',
			'Programming Language :: Python :: 3.10',
			'Programming Language :: Python :: 3.11',
			'License :: OSI Approved :: BSD License'
		],

		author                        = 'mentalblood',
		author_email                  = 'neceporenkostepan@gmail.com',
		maintainer                    = 'mentalblood',
		maintainer_email              = 'neceporenkostepan@gmail.com',

		packages                      = packages,
		package_data                  = {
			name: ['py.typed']
			for name in packages
		},
		ext_modules                   = [
			setuptools.Extension(
				name               = 'drunk_snail_python',
				sources            = [
					str(p)
					for p in (pathlib.Path('drunk_snail') / 'drunk_snail_python').rglob('*.c')
				],
				extra_compile_args = ['-O3']
			)
		]

	)
