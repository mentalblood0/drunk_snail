from drunk_snail import setKeywords, addTemplate, compile



one_character_keywords = {
	'open_tag': '(',
	'close_tag': ')',
	'param_operator': '$',
	'optional_operator': '?',
	'ref_operator': '~'
}


def test_basic():
	
	addTemplate(
		'CanonicalizationMethod', 
		'templates/CanonicalizationMethod_another_syntax.xml', 
		{
			'open_tag': '(',
			'close_tag': ')',
			'param_operator': '[purum]',
			'optional_operator': '{optionalno}'
		}
	)
	
	result = compile('CanonicalizationMethod')
	with open('tests/CanonicalizationMethod_another_syntax_result.py', 'w') as f:
		f.write(result)
	with open('tests/CanonicalizationMethod_correct_result.py') as f:
		correct_result = f.read()
	
	assert result == correct_result


def test_one_character_keywords():
	
	addTemplate(
		'CanonicalizationMethod', 
		'templates/CanonicalizationMethod_another_syntax__one_character_keywords.xml', 
		one_character_keywords
	)
	
	result = compile('CanonicalizationMethod')
	with open('tests/CanonicalizationMethod_another_syntax__one_character_keywords_result.py', 'w') as f:
		f.write(result)
	with open('tests/CanonicalizationMethod_correct_result.py') as f:
		correct_result = f.read()
	
	assert result == correct_result


def test_with_references_one_character_keywords():
	
	addTemplate('IssuerSerial', 'templates/IssuerSerial_another_syntax__one_character_keywords.xml')
	addTemplate('DataReference', 'templates/DataReference.xml')
	addTemplate('EncryptedKey', 'templates/EncryptedKey_another_syntax__one_character_keywords.xml')
	
	setKeywords(['EncryptedKey', 'IssuerSerial'], one_character_keywords)
	
	result = compile('EncryptedKey')
	with open('tests/EncryptedKey_another_syntax__one_character_keywords_result.py', 'w') as f:
		f.write(result)
	with open('tests/EncryptedKey_correct_result.py') as f:
		correct_result = f.read()
	
	assert result == correct_result