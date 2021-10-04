from drunk_snail import addTemplate, compile, Template



def test_basic():
	
	# addTemplate('CanonicalizationMethod', 'templates/CanonicalizationMethod.xml')
	t = Template('CanonicalizationMethod', 'templates/CanonicalizationMethod.xml')
	
	result = t.compiled
	with open('tests/CanonicalizationMethod_result.py', 'w') as f:
		f.write(result)
	with open('tests/CanonicalizationMethod_correct_result.py') as f:
		correct_result = f.read()
	
	assert result == correct_result


def test_with_references():

	addTemplate('EncryptedKey', 'templates/EncryptedKey.xml')
	addTemplate('IssuerSerial', 'templates/IssuerSerial.xml')
	addTemplate('DataReference', 'templates/DataReference.xml')

	result = compile('EncryptedKey')
	with open('tests/EncryptedKey_result.py', 'w') as f:
		f.write(result)
	with open('tests/EncryptedKey_correct_result.py') as f:
		correct_result = f.read()
	
	assert result == correct_result