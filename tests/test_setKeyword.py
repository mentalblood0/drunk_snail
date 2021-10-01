from drunk_snail import setKeyword, addTemplate, compileString



def test_basic():

	setKeyword('open_tag', '(')
	setKeyword('close_tag', ')')
	setKeyword('param_operator', '[purum]')
	setKeyword('optional_operator', '{optionalno}')

	with open('templates/CanonicalizationMethod_another_syntax.xml') as f:
		s = f.read()
	
	result = compileString(s, 'CanonicalizationMethod')
	with open('tests/CanonicalizationMethod_another_syntax_result.py', 'w') as f:
		f.write(result)
	with open('tests/CanonicalizationMethod_correct_result.py') as f:
		correct_result = f.read()
	
	assert result == correct_result


def test_one_character_keywords():

	setKeyword('open_tag', '(')
	setKeyword('close_tag', ')')
	setKeyword('param_operator', '$')
	setKeyword('optional_operator', '?')

	with open('templates/CanonicalizationMethod_another_syntax__one_character_keywords.xml') as f:
		s = f.read()
	
	result = compileString(s, 'CanonicalizationMethod')
	with open('tests/CanonicalizationMethod_another_syntax__one_character_keywords_result.py', 'w') as f:
		f.write(result)
	with open('tests/CanonicalizationMethod_correct_result.py') as f:
		correct_result = f.read()
	
	assert result == correct_result


def test_with_references_one_character_keywords():

	setKeyword('open_tag', '(')
	setKeyword('close_tag', ')')
	setKeyword('param_operator', '$')
	setKeyword('optional_operator', '?')
	setKeyword('ref_operator', '~')

	addTemplate('IssuerSerial', 'templates/IssuerSerial_another_syntax__one_character_keywords.xml')
	addTemplate('DataReference', 'templates/DataReference_another_syntax__one_character_keywords.xml')

	with open('templates/EncryptedKey_another_syntax__one_character_keywords.xml') as f:
		s = f.read()
	
	result = compileString(s, 'EncryptedKey')
	with open('tests/EncryptedKey_another_syntax__one_character_keywords_result.py', 'w') as f:
		f.write(result)
	with open('tests/EncryptedKey_correct_result.py') as f:
		correct_result = f.read()
	
	assert result == correct_result