from drunk_snail import setKeyword, addTemplate, compileString



def test_basic():

	# setKeyword('open_tag', '<<')
	# setKeyword('close_tag', '>>')
	setKeyword('param_operator', '[purum]')
	setKeyword('optional_operator', '{optionalno}')

	with open('templates/CanonicalizationMethod_another_syntax.xml') as f:
		s = f.read()
	
	result = compileString(s, 'CanonicalizationMethod')
	with open('CanonicalizationMethod_another_syntax_result.py', 'w') as f:
		f.write(result)
	with open('test/CanonicalizationMethod_correct_result.py') as f:
		correct_result = f.read()
	
	assert result == correct_result


# def test_with_references():

# 	addTemplate('IssuerSerial', 'templates/IssuerSerial.xml')
# 	addTemplate('DataReference', 'templates/DataReference.xml')

# 	with open('templates/EncryptedKey.xml') as f:
# 		s = f.read()
	
# 	result = compileString(s, 'EncryptedKey')
# 	with open('test/EncryptedKey_correct_result.py') as f:
# 		correct_result = f.read()
	
# 	assert result == correct_result