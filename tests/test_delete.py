import glob
from multiprocessing.pool import ThreadPool

from drunk_snail import Template
from drunk_snail.sources import FileSource



def test_many():

	args = []
	for path in glob.iglob('templates_/**.*', recursive=True):
		
		name = path.split('\\')[1].split('.')[0]
		args.append((name, FileSource(path, watch=False)))

	for i in range(2):

		templates = [
			Template(*a)
			for a in args
		]

		for t in templates:
			t.compiled
		
		ThreadPool(len(templates) or 1).map(
			lambda t: t.delete(),
			templates
		)