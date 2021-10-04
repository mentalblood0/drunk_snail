from drunk_snail import Template
from drunk_snail.sources import FileSource



one_character_keywords = {
	'open_tag': '(',
	'close_tag': ')',
	'param_operator': '$',
	'optional_operator': '?',
	'ref_operator': '~'
}


def test_basic():
	
	canonicalization_method = Template(
		'CanonicalizationMethod', 
		FileSource('templates/CanonicalizationMethod_another_syntax.xml'), 
		{
			'open_tag': '(',
			'close_tag': ')',
			'param_operator': '[purum]',
			'optional_operator': '{optionalno}'
		}
	)
	
	result = canonicalization_method.compiled
	with open('tests/CanonicalizationMethod_another_syntax_result.py', 'w') as f:
		f.write(result)
	with open('tests/CanonicalizationMethod_correct_result.py') as f:
		correct_result = f.read()
	
	assert result == correct_result


def test_one_character_keywords():
	
	canonicalization_method = Template(
		'CanonicalizationMethod', 
		FileSource('templates/CanonicalizationMethod_another_syntax__one_character_keywords.xml'), 
		one_character_keywords
	)
	
	result = canonicalization_method.compiled
	with open('tests/CanonicalizationMethod_another_syntax__one_character_keywords_result.py', 'w') as f:
		f.write(result)
	with open('tests/CanonicalizationMethod_correct_result.py') as f:
		correct_result = f.read()
	
	assert result == correct_result


def test_with_references_one_character_keywords():
	
	issuer_serial = Template('IssuerSerial', FileSource('templates/IssuerSerial_another_syntax__one_character_keywords.xml'))
	Template('DataReference', FileSource('templates/DataReference.xml'))
	encrypted_key = Template('EncryptedKey', FileSource('templates/EncryptedKey_another_syntax__one_character_keywords.xml'))
	
	issuer_serial.setKeywords(one_character_keywords)
	encrypted_key.setKeywords(one_character_keywords)
	
	result = encrypted_key.compiled
	with open('tests/EncryptedKey_another_syntax__one_character_keywords_result.py', 'w') as f:
		f.write(result)
	with open('tests/EncryptedKey_correct_result.py') as f:
		correct_result = f.read()
	
	assert result == correct_result