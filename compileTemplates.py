import os
import glob
import shutil
from drunk_snail import Template
from drunk_snail.sources import FileSource



shutil.rmtree('compiled_templates_', ignore_errors=True)
os.mkdir('compiled_templates_')

names = []
for path in glob.iglob('templates_/**.*', recursive=True):
	
	name = path.split('\\')[1].split('.')[0]
	names.append(name)

	Template(name, FileSource(path, watch=False))

for n in names:

	t = Template(n)
	print(Template(n).source.path)
	
	compiled = Template(n).compiled
	with open(f"compiled_templates_\\{t.name}.py", 'w') as f:
		f.write(compiled)