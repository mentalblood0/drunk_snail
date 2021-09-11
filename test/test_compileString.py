from drunk_snail import addTemplate, compileString



def test_basic():

	with open('templates/CanonicalizationMethod.xml') as f:
		s = f.read()
	
	result = compileString(s, 'CanonicalizationMethod')
	with open('test/CanonicalizationMethod_correct_result.py') as f:
		correct_result = f.read()
	
	assert result == correct_result


def test_with_references():

	addTemplate('IssuerSerial', 'templates/IssuerSerial.xml')
	addTemplate('DataReference', 'templates/DataReference.xml')

	with open('templates/EncryptedKey.xml') as f:
		s = f.read()
	
	result = compileString(s, 'EncryptedKey')
	with open('test/EncryptedKey_correct_result.py') as f:
		correct_result = f.read()
	
	assert result == correct_result