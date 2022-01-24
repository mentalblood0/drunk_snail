from re import template
from time import sleep
from threading import Thread
from drunk_snail import Template
from drunk_snail.sources import StringSource



def test_create_show():

	template_name = 'test_create_show'

	def create():
		Template(template_name, StringSource('lalala'))

	def show():
		print(Template(template_name))

	t = Thread(target=create)
	t.start()
	t.join()
	
	t = Thread(target=show)
	t.start()
	t.join()