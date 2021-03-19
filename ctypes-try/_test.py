from ctypes import *

class CustomStruct(Structure):
	_fields_ = [('a', c_int)]

struct = CustomStruct(1)
p_struct = pointer(struct)
print(p_struct.contents)