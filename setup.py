import glob
from setuptools import setup, Extension, find_packages



def paths(root: str, extension: str):
	return glob.glob(f'{root}/*.{extension}') + glob.glob(f'{root}/**/*.{extension}', recursive=True)


if __name__ == '__main__':
	
	try:
		with open('README.md') as f:
			long_description = f.read()
	except FileNotFoundError:
		long_description = ''

	setup(
		name='drunk_snail',
		version='7.0.1',
		description='Simple template engine. Faster than you think',
		long_description=long_description,
		long_description_content_type='text/markdown',
		author='mentalblood',
		author_email='neceporenkostepan@gmail.com',
		maintainer='mentalblood',
		maintainer_email='neceporenkostepan@gmail.com',
		keywords=['template-engine', 'ragel'],
		url='https://github.com/MentalBlood/drunk_snail',
		python_requires='>=3.5',

		packages=find_packages(),
		ext_modules=[
			Extension(
				name='drunk_snail_python',
				sources=paths('drunk_snail/drunk_snail_python', 'c'),
				extra_compile_args=[]
			)
		],
		data_files=paths('drunk_snail/drunk_snail_python', 'c') + paths('drunk_snail/drunk_snail_python', 'h')
	)
