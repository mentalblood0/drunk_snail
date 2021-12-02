from drunk_snail import Template
from drunk_snail.sources import FileSource



def test_basic():
	
	t = Template('CanonicalizationMethod', FileSource('templates/CanonicalizationMethod.xml'))
	
	result = t.compiled
	with open('tests/CanonicalizationMethod_result.py', 'w') as f:
		f.write(result)
	with open('tests/CanonicalizationMethod_correct_result.py') as f:
		correct_result = f.read()
	
	assert result == correct_result


def test_with_references():

	encrypted_key = Template('EncryptedKey', FileSource('templates/EncryptedKey.xml'))
	issuer_serial = Template('IssuerSerial', FileSource('templates/IssuerSerial.xml'))
	data_reference = Template('DataReference', FileSource('templates/DataReference.xml'))

	result = encrypted_key.compiled
	with open('tests/EncryptedKey_result.py', 'w') as f:
		f.write(result)
	with open('tests/EncryptedKey_correct_result.py') as f:
		correct_result = f.read()
	
	assert result == correct_result


def test_endpoint_template():

	t = Template('test_compile_endpoint_template', FileSource('templates/endpoint_template.txt', watch=False))

	assert t.compiled
	assert t()