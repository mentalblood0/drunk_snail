from ctypes import *

ctypes_type_from_python_type = {
	str: c_wchar_p,
	bytes: c_char_p,
	int: c_int,
	float: c_float
}

def dictToStructure(d, root=True):
	fields = []
	for key, value in d.items():
		if type(value) == dict:
			substructure_def = dictToStructure(value, root=False)
			value_c_type = POINTER(substructure_def)
			substructure = substructure_def(**value)
			d[key] = pointer(substructure)
		elif type(value) == list:
			example_element = value[0]
			if type(example_element) == dict:
				substructure_def = dictToStructure(value, root=False)
		else:
			value_c_type = ctypes_type_from_python_type[type(value)]
		fields.append((
			key,
			value_c_type
		))
	class Dict(Structure):
		_fields_ = fields
	return Dict if not root else Dict(**d)

d = lambda: {
	'Header': {
		'lifecycle_id': '1000230022021021800000002',
		'addressing_to': [
			'100000003',
			'100000004',
			'100000005'
		],
		'from_address': 'http://www.any.com/circum/regemque',
		'reply_to_address': 'http://www.test.com/foedere/ferant',
		'service_name': 'qname',
		'message_id': '1000000032021021800005059',
		'Security': {
			'created': '2016-10-07T18:24:19+03:00',
			'expires': '2002-11-05T11:30:58',
			'CanonicalizationMethod': {
				'ignore_comments': 'false',
				'trim_text_nodes': 'true',
				'prefix_rewrite': 'sequential',
				'qname_aware_element': 'http://www.sample.edu/soror/abdidit',
				# 'qname_aware_qualified_attr': 'some attr'
			},
			'Reference': [{
					'ignore_comments': 'false',
					'trim_text_nodes': 'true',
					'prefix_rewrite': 'sequential',
					'qname_aware_element': 'http://www.sample.edu/soror/abdidit',
					# 'qname_aware_qualified_attr': 'some attr',
					'digest_method': 'urn:ietf:params:xml:ns:cpxmlsec:algorithms:gostr3411',
					'digest_value': 'YXRyaXNhdHJpc2F0cmlzYXRyaXNhdHJpc2F0cmlzYXQ='
				},{
					'ignore_comments': 'true',
					'trim_text_nodes': 'false',
					'prefix_rewrite': 'sequential',
					'qname_aware_element': 'http://www.sample.edu/soror/abdidit',
					# 'qname_aware_qualified_attr': 'some attr',
					'digest_method': 'urn:ietf:params:xml:ns:cpxmlsec:algorithms:gostr3411',
					'digest_value': 'YXRyaXNhdHJpc2F0cmlzYXRyaXNhdHJpc2F0cmlzYXQ='
				},{
					'ignore_comments': 'true',
					'trim_text_nodes': 'true',
					'prefix_rewrite': 'sequential',
					'qname_aware_element': 'http://www.sample.edu/soror/abdidit',
					# 'qname_aware_qualified_attr': 'some attr',
					'digest_method': 'urn:ietf:params:xml:ns:cpxmlsec:algorithms:gostr3411',
					'digest_value': 'YXRyaXNhdHJpc2F0cmlzYXRyaXNhdHJpc2F0cmlzYXQ='
				}
			],
			'signature_value': 'aW1wb3N1aXRpbXBvc3VpdGltcG9zdWl0aW1wb3N1aXRpbXBvc3VpdGltcG9zdWl0aW1wb3N1aXRpbXBvc3VpdA==',
			'certificate': 'YXRyaXNhdHJpc2F0cmlzYXRyaXNhdHJpc2F0cmlzYXRyaXNhdHJpc2F0cmlzYXRyaXNhdHJpc2F0cmlzYXRyaXNhdHJpc2F0cmlzYXRyaXNhdHJpc2F0cmlzYXRyaXNhdHJpc2F0cmlzYXRyaXNhdHJpc2F0cmlzYXRyaXNhdHJpc2F0cmlzYXRyaXNhdHJpc2F0cmlzYXRyaXNhdHJpcw==',
			'EncryptedKey': [{
					'encryption_method': 'urn:ietf:params:xml:ns:cpxmlsec:algorithms:transport-gost2012-512',
					'IssuerSerial': {
						'name': 'string',
						'serial': '100'
					},
					'cipher_value': 'c29ub3Jhcw==',
					'DataReference': [
						{'uri': 'string1'},
						{'uri': 'string1'},
						{'uri': 'string1'}
					]
				},{
					'encryption_method': 'urn:ietf:params:xml:ns:cpxmlsec:algorithms:transport-gost2012-512',
					'IssuerSerial': {
						'name': 'string',
						'serial': '100'
					},
					'cipher_value': 'c29ub3Jhcw==',
					'DataReference': [
						{'uri': 'string1'},
						{'uri': 'string1'},
						{'uri': 'string1'}
					]
				}
			],
		}
	},
	'notification_text': ['обработано', 'lalala']
}

import random
import string

def randomString(n):
	return ''.join(random.choices(string.ascii_uppercase + string.digits, k=n))

params = {
	'TableRow': [{
		'TableData': [{
			'data': randomString(8)
		} for i in range(1000)]
	} for i in range(10)]
}

import cProfile
import json
cProfile.run('''
for i in range(1000):
	py_object(d())
''')
exit()

lib = cdll['./test.so']

printSimpleStruct = lib['printSimpleStruct']
printSimpleStruct.argtypes = [c_void_p]

# import cProfile

# cProfile.run('''
# for i in range(1000):
# 	dictToStructure(d());
# ''')

dict_struct = dictToStructure(d())
printSimpleStruct(byref(dict_struct))