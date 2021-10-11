import requests
from functools import partial



class User:

	def __init__(self, host, port):
		
		self.host = host
		self.port = port

		for method in ['get', 'post', 'put', 'delete']:
			setattr(
				self, 
				method, 
				partial(self.makeRequest, method=method)
			)
	
	def makeRequest(self, resource, code, data=None, method=None):

		response = getattr(requests, method)(f"http://{self.host}:{self.port}{resource}", json=data)
		if response.status_code != code:
			raise Exception(f'Wrong status code: {response.status_code} (expected {code})')

		if response.json() != None:
			return response.json()



import sys
sys.modules[__name__] = User