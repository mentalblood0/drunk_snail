def render(IssuerSerial):
	result = ''
	result += f'''<xd:X509IssuerSerial>\n'''
	for name in ([None] if ((not IssuerSerial) or (not 'name' in IssuerSerial)) else (IssuerSerial['name'] if type(IssuerSerial['name']) == list else [IssuerSerial['name']])):
		result += f'''    <xd:X509IssuerName>{name}</xd:X509IssuerName>\n'''
	for serial in ([None] if ((not IssuerSerial) or (not 'serial' in IssuerSerial)) else (IssuerSerial['serial'] if type(IssuerSerial['serial']) == list else [IssuerSerial['serial']])):
		result += f'''    <xd:X509Serial>{serial}</xd:X509Serial>\n'''
	result += f'''</xd:X509IssuerSerial>\n'''
	return result
