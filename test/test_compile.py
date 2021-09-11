from drunk_snail import addTemplate, compile



def test_basic():
	
	addTemplate('CanonicalizationMethod', 'templates/CanonicalizationMethod.xml')
	
	result = compile('CanonicalizationMethod')
	with open('test/CanonicalizationMethod_correct_result.py') as f:
		correct_result = f.read()
	
	assert result == correct_result


def test_with_references():

	addTemplate('EncryptedKey', 'templates/EncryptedKey.xml')
	addTemplate('IssuerSerial', 'templates/IssuerSerial.xml')
	addTemplate('DataReference', 'templates/DataReference.xml')

	result = compile('EncryptedKey')
	with open('test/EncryptedKey_correct_result.py') as f:
		correct_result = f.read()
	
	assert result == correct_result