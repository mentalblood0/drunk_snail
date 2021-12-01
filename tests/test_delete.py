import glob
from multiprocessing.pool import ThreadPool

from drunk_snail import Template
from drunk_snail.sources import FileSource



def test_many():

	templates = []
	for path in glob.iglob('templates_/**.*', recursive=True):
		
		name = path.split('\\')[1].split('.')[0]

		templates.append(
			Template(name, FileSource(path, watch=False))
		)

	for t in templates:
		print(t.source.path)
		t.compiled
	
	ThreadPool(8).map(
		lambda t: t.delete(),
		templates
	)