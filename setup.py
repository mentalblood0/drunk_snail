import os
from distutils.core import setup



if __name__ == '__main__':

	long_description = ''
	if os.path.exists('README.md'):
		with open('README.md') as f:
			long_description = f.read()

	setup(
		name='broker_tester',
		version='0.1.0',
		description='Tester for broker services',
		long_description=long_description,
		long_description_content_type='text/markdown',
		author='mentalblood',
		packages=['broker_tester', 'broker_tester.subcommands']
	)