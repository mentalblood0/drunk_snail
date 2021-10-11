from drunk_snail import Template
from drunk_snail.sources import StringSource, FileSource



def test_basic():

	with open('templates/CanonicalizationMethod.xml') as f:
		s = f.read()
	
	result = Template('CanonicalizationMethod', StringSource(s)).compiled
	with open('tests/CanonicalizationMethod_correct_result.py') as f:
		correct_result = f.read()
	
	assert result == correct_result


def test_with_references():

	Template('IssuerSerial', FileSource('templates/IssuerSerial.xml'))
	Template('DataReference', FileSource('templates/DataReference.xml'))

	with open('templates/EncryptedKey.xml') as f:
		s = f.read()
	
	result = Template('EncryptedKey', StringSource(s)).compiled
	with open('tests/EncryptedKey_correct_result.py') as f:
		correct_result = f.read()
	
	assert result == correct_result