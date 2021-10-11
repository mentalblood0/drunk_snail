from . import User



class Module(User):

	def __init__(self, *args, **kwargs):
		super().__init__(*args, **kwargs)
	
	def sessions_get(self):
		return self.get('/sessions', 200)



import sys
sys.modules[__name__] = Module