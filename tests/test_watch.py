import os
from time import sleep
from drunk_snail import Template
from drunk_snail.sources import FileSource



def test_basic():

	file_path = 'test_watch_temp_file.txt'

	with open(file_path, 'w') as f:
		f.write('<!-- (param)x -->')
	
	t = Template('test_watch_basic', FileSource(file_path))
	assert t({'x': 'a'}) == 'a'

	with open(file_path, 'a') as f:
		f.write('\n<!-- (param)y -->')
	
	sleep(1)
	assert t({'x': 'a', 'y': 'b'}) == 'a\nb'

	del t
	os.remove(file_path)


def test_disable_watch():

	file_path = 'test_watch_temp_file.txt'

	with open(file_path, 'w') as f:
		f.write('<!-- (param)x -->')
	
	t = Template('test_watch_basic', FileSource(file_path, watch=False))
	assert t({'x': 'a'}) == 'a'

	with open(file_path, 'a') as f:
		f.write('\n<!-- (param)y -->')
	
	sleep(1)
	assert t({'x': 'a', 'y': 'b'}) == 'a'

	del t
	os.remove(file_path)