from re import template
from time import sleep
from threading import Thread
from drunk_snail import Template
from drunk_snail.sources import StringSource



def test_create_show():

	name = 'test_create_show'
	text = 'lalala'

	def create():
		Template(name, StringSource(text))

	def show():
		assert Template(name).text == text

	t = Thread(target=create)
	t.start()
	t.join()
	
	t = Thread(target=show)
	t.start()
	t.join()