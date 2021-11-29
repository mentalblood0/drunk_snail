def render(EncryptedKey):
	result = ''
	result += f'''<xe:EncryptedKey wsu:Id="string">\n'''
	for encryption_method in ([None] if ((not EncryptedKey) or (not 'encryption_method' in EncryptedKey)) else (EncryptedKey['encryption_method'] if type(EncryptedKey['encryption_method']) == list else [EncryptedKey['encryption_method']])):
		result += f'''    <xe:EncryptionMethod xe:Algorithm="{encryption_method}"/>\n'''
	result += f'''    <xe:KeyInfo wsu:Id="string">\n'''
	result += f'''        <xd:X509Data>\n'''
	result += f'''            <!--You have a CHOICE of the next 3 items at this level-->\n'''
	if EncryptedKey and 'x509_certificate' in EncryptedKey:
		for x509_certificate in ([None] if ((not EncryptedKey) or (not 'x509_certificate' in EncryptedKey)) else (EncryptedKey['x509_certificate'] if type(EncryptedKey['x509_certificate']) == list else [EncryptedKey['x509_certificate']])):
			result += f'''            <xd:X509Certificate>{x509_certificate}</xd:X509Certificate>\n'''
	if EncryptedKey and 'x509_ski' in EncryptedKey:
		for x509_ski in ([None] if ((not EncryptedKey) or (not 'x509_ski' in EncryptedKey)) else (EncryptedKey['x509_ski'] if type(EncryptedKey['x509_ski']) == list else [EncryptedKey['x509_ski']])):
			result += f'''            <xd:X509SKI>{x509_ski}</xd:X509SKI>\n'''
	if EncryptedKey and 'IssuerSerial' in EncryptedKey:
		for IssuerSerial in ([None] if ((not EncryptedKey) or (not 'IssuerSerial' in EncryptedKey)) else (EncryptedKey['IssuerSerial'] if type(EncryptedKey['IssuerSerial']) == list else [EncryptedKey['IssuerSerial']])):
			result += f'''            <xd:X509IssuerSerial>\n'''
			for name in ([None] if ((not IssuerSerial) or (not 'name' in IssuerSerial)) else (IssuerSerial['name'] if type(IssuerSerial['name']) == list else [IssuerSerial['name']])):
				result += f'''                <xd:X509IssuerName>{name}</xd:X509IssuerName>\n'''
			for serial in ([None] if ((not IssuerSerial) or (not 'serial' in IssuerSerial)) else (IssuerSerial['serial'] if type(IssuerSerial['serial']) == list else [IssuerSerial['serial']])):
				result += f'''                <xd:X509Serial>{serial}</xd:X509Serial>\n'''
			result += f'''            </xd:X509IssuerSerial>\n'''
	result += f'''        </xd:X509Data>\n'''
	result += f'''    </xe:KeyInfo>\n'''
	result += f'''    <xe:CipherData>\n'''
	for cipher_value in ([None] if ((not EncryptedKey) or (not 'cipher_value' in EncryptedKey)) else (EncryptedKey['cipher_value'] if type(EncryptedKey['cipher_value']) == list else [EncryptedKey['cipher_value']])):
		result += f'''        <xe:CipherValue>{cipher_value}</xe:CipherValue>\n'''
	result += f'''    </xe:CipherData>\n'''
	result += f'''    <xe:ReferenceList>\n'''
	result += f'''        <!--1 or more repetitions:-->\n'''
	for DataReference in ([None] if ((not EncryptedKey) or (not 'DataReference' in EncryptedKey)) else (EncryptedKey['DataReference'] if type(EncryptedKey['DataReference']) == list else [EncryptedKey['DataReference']])):
		for uri in ([None] if ((not DataReference) or (not 'uri' in DataReference)) else (DataReference['uri'] if type(DataReference['uri']) == list else [DataReference['uri']])):
			result += f'''        <xe:DataReference xe:URI="{uri}"/>\n'''
	result += f'''    </xe:ReferenceList>\n'''
	result += f'''</xe:EncryptedKey>'''
	return result
