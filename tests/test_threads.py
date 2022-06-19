from threading import Thread
from drunk_snail import Template



def test_create_show():

	name = 'test_create_show'
	text = 'lalala'

	def create():
		Template(name, text)

	def show():
		assert Template(name).text == text

	t = Thread(target=create)
	t.start()
	t.join()
	
	t = Thread(target=show)
	t.start()
	t.join()