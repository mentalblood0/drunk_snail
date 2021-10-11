from . import User



class Client(User):

	def __init__(self, *args, **kwargs):
		super().__init__(*args, **kwargs)
	
	def sessions_post(self, name):
		return self.post('/sessions', 200, {
			'name': name
		})



import sys
sys.modules[__name__] = Client