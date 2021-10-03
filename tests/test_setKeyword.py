from drunk_snail import setKeyword, addTemplate, compile



def test_basic():
	
	addTemplate('CanonicalizationMethod', 'templates/CanonicalizationMethod_another_syntax.xml')
	setKeyword('CanonicalizationMethod', 'open_tag', '(')
	setKeyword('CanonicalizationMethod', 'close_tag', ')')
	setKeyword('CanonicalizationMethod', 'param_operator', '[purum]')
	setKeyword('CanonicalizationMethod', 'optional_operator', '{optionalno}')
	
	result = compile('CanonicalizationMethod')
	with open('tests/CanonicalizationMethod_another_syntax_result.py', 'w') as f:
		f.write(result)
	with open('tests/CanonicalizationMethod_correct_result.py') as f:
		correct_result = f.read()
	
	assert result == correct_result


def test_one_character_keywords():
	
	addTemplate('CanonicalizationMethod', 'templates/CanonicalizationMethod_another_syntax__one_character_keywords.xml')
	setKeyword('CanonicalizationMethod', 'open_tag', '(')
	setKeyword('CanonicalizationMethod', 'close_tag', ')')
	setKeyword('CanonicalizationMethod', 'param_operator', '$')
	setKeyword('CanonicalizationMethod', 'optional_operator', '?')
	
	result = compile('CanonicalizationMethod')
	with open('tests/CanonicalizationMethod_another_syntax__one_character_keywords_result.py', 'w') as f:
		f.write(result)
	with open('tests/CanonicalizationMethod_correct_result.py') as f:
		correct_result = f.read()
	
	assert result == correct_result


def test_with_references_one_character_keywords():
	
	addTemplate('IssuerSerial', 'templates/IssuerSerial_another_syntax__one_character_keywords.xml')
	setKeyword('IssuerSerial', 'open_tag', '(')
	setKeyword('IssuerSerial', 'close_tag', ')')
	setKeyword('IssuerSerial', 'param_operator', '$')
	setKeyword('IssuerSerial', 'optional_operator', '?')
	setKeyword('IssuerSerial', 'ref_operator', '~')

	addTemplate('DataReference', 'templates/DataReference.xml')
	
	addTemplate('EncryptedKey', 'templates/EncryptedKey_another_syntax__one_character_keywords.xml')
	setKeyword('EncryptedKey', 'open_tag', '(')
	setKeyword('EncryptedKey', 'close_tag', ')')
	setKeyword('EncryptedKey', 'param_operator', '$')
	setKeyword('EncryptedKey', 'optional_operator', '?')
	setKeyword('EncryptedKey', 'ref_operator', '~')
	
	result = compile('EncryptedKey')
	with open('tests/EncryptedKey_another_syntax__one_character_keywords_result.py', 'w') as f:
		f.write(result)
	with open('tests/EncryptedKey_correct_result.py') as f:
		correct_result = f.read()
	
	assert result == correct_result