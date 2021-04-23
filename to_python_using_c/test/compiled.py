def renderNotificationTemplate(Notification):
	result = ''
	result += f'''<?xml version="1.0"?>\n'''
	for namespaces in ([None] if ((not Notification) or (not 'namespaces' in Notification)) else (Notification['namespaces'] if type(Notification['namespaces']) == list else [Notification['namespaces']])):
		result += f'''<soapenv:Envelope xmlns:soapenv="http://schemas.xmlsoap.org/soap/envelope/" xmlns:sch="http://xsd.gspvd/v001/schvr" xmlns:wsu="http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-utility-1.0.xsd" xmlns:add="http://xsd.gspvd/v001/addressing" xmlns:xd="http://www.w3.org/2000/09/xmldsig#" xmlns:xd1="http://www.w3.org/2010/xmldsig2#" xmlns:x-="http://www.w3.org/2010/xml-c14n2" xmlns:oas="http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-secext-1.0.xsd" xmlns:xe="http://www.w3.org/2001/04/xmlenc#" xmlns:prin="http://xsd.gspvd/v001/personalization/pc/print-tasks" xmlns:com="http://xsd.gspvd/v001/personalization/request/common" xmlns:com1="http://xsd.gspvd/v001/common-data" xmlns:pas="http://xsd.gspvd/v001/personalization/request/passport" xmlns:trav="http://xsd.gspvd/v001/personalization/request/travel-document" xmlns:res="http://xsd.gspvd/v001/personalization/request/residence-permit" xmlns:res1="http://xsd.gspvd/v001/personalization/response" xmlns:req="http://xsd.gspvd/v001/personalization/request" xmlns:form="http://xsd.gspvd/v001/forms/form" xmlns:com2="http://xsd.gspvd/v001/forms/common" xmlns:mat="http://xsd.gspvd/v001/forms/passport/mature" xmlns:per="http://xsd.gspvd/v001/forms/internal/person-data-change" xmlns:per1="http://xsd.gspvd/v001/forms/internal/person-address" xmlns:con="http://xsd.gspvd/v001/forms/internal/control-info" xmlns:per2="http://xsd.gspvd/v001/forms/internal/person-relatives" xmlns:emp="http://xsd.gspvd/v001/forms/internal/employment-history" xmlns:chil="http://xsd.gspvd/v001/forms/passport/child" xmlns:ser="http://xsd.gspvd/v001/forms/passport/service-diplomatic" xmlns:trav1="http://xsd.gspvd/v001/forms/travel-document" xmlns:trav2="http://xsd.gspvd/v001/forms/travel-document-adult" xmlns:trav3="http://xsd.gspvd/v001/forms/travel-document-adult-metrics" xmlns:trav4="http://xsd.gspvd/v001/forms/travel-document-adult-biometrics" xmlns:trav5="http://xsd.gspvd/v001/forms/travel-document-child" xmlns:trav6="http://xsd.gspvd/v001/forms/travel-document-child-yml" xmlns:trav7="http://xsd.gspvd/v001/forms/travel-document-child-metrics" xmlns:res2="http://xsd.gspvd/v001/forms/residence-permit" xmlns:pgs="http://xsd.gspvd/v001/forms/passport/pgs-child" xmlns:pgs1="http://xsd.gspvd/v001/forms/passport/pgs-mature" xmlns:res3="http://xsd.gspvd/v001/forms/residence-permit-adult-metrics-v1" xmlns:res4="http://xsd.gspvd/v001/forms/residence-permit-adult-v1" xmlns:res5="http://xsd.gspvd/v001/forms/residence-permit-child-incapable-metrics-v1" xmlns:res6="http://xsd.gspvd/v001/forms/residence-permit-child-incapable-v1" xmlns:res7="http://xsd.gspvd/v001/forms/residence-permit-replacement-metrics-v1" xmlns:res8="http://xsd.gspvd/v001/forms/residence-permit-replacement-v1" xmlns:res9="http://xsd.gspvd/v001/forms/residence-permit-duplicate-metrics-v1" xmlns:res10="http://xsd.gspvd/v001/forms/residence-permit-duplicate-v1" xmlns:res11="http://xsd.gspvd/v001/forms/residence-permit-correction-metrics-v1" xmlns:res12="http://xsd.gspvd/v001/forms/residence-permit-correction-v1" xmlns:faul="http://xsd.gspvd/v001/utility/faults" xmlns:all="http://xsd.gspvd/v001/personalization/allowed" xmlns:lif="http://xsd.gspvd/v001/lifecycle-state" xmlns:res13="http://xsd.gspvd/v001/approvals/response" xmlns:com3="http://xsd.gspvd/v001/approvals/common" xmlns:req1="http://xsd.gspvd/v001/approvals/requisition" xmlns:form1="http://xsd.gspvd/v001/approvals/form" xmlns:cdb="http://xsd.gspvd/v001/approvals/cdb-response" xmlns:req2="http://xsd.gspvd/v001/approvals/request" xmlns:cdb1="http://xsd.gspvd/v001/approvals/cdb-request" xmlns:not="http://xsd.gspvd/v001/utility/notification" xmlns:dpc="http://xsd.gspvd/v001/personalization/pc/dpc-notifications" xmlns:req3="http://xsd.gspvd/v001/GISMU/request" xmlns:com4="http://xsd.gspvd/v001/GISMU/common-data" xmlns:dos="http://xsd.gspvd/v001/GISMU/residence-permit/dossier" xmlns:res14="http://xsd.gspvd/v001/GISMU/response" xmlns:dos1="http://xsd.gspvd/v001/GISMU/refugee-travel/dossier" xmlns:cdb2="http://xsd.gspvd/v001/cdb/cdb-type" xmlns:cdb3="http://xsd.gspvd/v001/cdb/cdb-search-request" xmlns:cdb4="http://xsd.gspvd/v001/cdb/cdb-search-response" xmlns:cdb5="http://xsd.gspvd/v001/cdb/cdb-annul-request" xmlns:cdb6="http://xsd.gspvd/v001/cdb/cdb-mrz-annul-request" xmlns:cdb7="http://xsd.gspvd/v001/cdb/cdb-annul-response" xmlns:cdb8="http://xsd.gspvd/v001/cdb/cdb-issuance-request" xmlns:cdb9="http://xsd.gspvd/v001/cdb/cdb-issuance-response" xmlns:arm="http://xsd.gspvd/v001/armus/armus-type" xmlns:arm1="http://xsd.gspvd/v001/armus/armus-operations" xmlns:arm2="http://xsd.gspvd/v001/armus/armus-common" xmlns:fron="http://xsd.gspvd/v001/frontier-segment" xmlns:req4="http://xsd.gspvd/v001/frontier-segment/border-intersection/request" xmlns:res15="http://xsd.gspvd/v001/frontier-segment/border-intersection/response" xmlns:fron1="http://xsd.gspvd/v001/GISMU/frontier-intersection" xmlns:res16="http://xsd.gspvd/v001/frontier-segment/federal-inquiry/response" xmlns:com5="http://xsd.gspvd/v001/frontier-segment/federal-inquiry/common" xmlns:req5="http://xsd.gspvd/v001/frontier-segment/federal-inquiry/request" xmlns:req6="http://xsd.gspvd/v001/frontier-segment/issued-document-data/request" xmlns:req7="http://xsd.gspvd/v001/frontier-segment/invalid-document-data/request" xmlns:fssp="http://xsd.gspvd/v001/frontier-segment/fssp-data" xmlns:cer="http://xsd.gspvd/v001/certificate-order" xmlns:cert="http://xsd.gspvd/v001/certificate-order/cert-order-form" xmlns:cert1="http://xsd.gspvd/v001/certificate-order/cert-order-cms" xmlns:cert2="http://xsd.gspvd/v001/certificate-order/cert-order-lifecycle-state" xmlns:okz="http://xsd.gspvd/v001/okz-request" xmlns:okz1="http://xsd.gspvd/v001/okz-request-ext" xmlns:pkr="http://xsd.gspvd/v001/pkrbp/pkrbp" xmlns:vs="http://xsd.gspvd/v001/vs" xmlns:ns="urn://visa.xs.gosniias/1.0.1" xmlns:pay="http://xsd.gspvd/v001/gisgmp/payment" xmlns:ns1="urn://roskazna.ru/gisgmp/xsd/services/export-payments/2.1.1" xmlns:ns2="http://roskazna.ru/gisgmp/xsd/SearchConditions/2.1.1" xmlns:ns3="http://roskazna.ru/gisgmp/xsd/Common/2.1.1" xmlns:typ="http://xsd.gspvd/v001/pgs/types" xmlns:eac="http://xsd.gspvd/v001/eac" xmlns:cert3="http://xsd.gspvd/v001/eac/cert-refs-request" xmlns:cert4="http://xsd.gspvd/v001/eac/cert-request" xmlns:cert5="http://xsd.gspvd/v001/eac/cert-response" xmlns:mfc="http://xsd.gspvd/v001/mfc" xmlns:ser1="http://xsd.gspvd/v001/utility/service" xmlns:e="http://xsd.gspvd/v001/e-visa" xmlns:fssp1="http://xsd.gspvd/v001/frontier-segment/fssp-data-async" xmlns:bor="http://xsd.gspvd/v001/frontier-segment/border-intersection/bordercrossing">\n'''
	for Header in ([None] if ((not Notification) or (not 'Header' in Notification)) else (Notification['Header'] if type(Notification['Header']) == list else [Notification['Header']])):
		result += f'''	<soapenv:Header>\n'''
		result += f'''		<add:Addressing wsu:Id="AddressingHeader">\n'''
		result += f'''			<add:LifecycleInfo>\n'''
		for lifecycle_id in ([None] if ((not Header) or (not 'lifecycle_id' in Header)) else (Header['lifecycle_id'] if type(Header['lifecycle_id']) == list else [Header['lifecycle_id']])):
			result += f'''				<add:LifecycleID>{lifecycle_id}</add:LifecycleID>\n'''
		result += f'''			</add:LifecycleInfo>\n'''
		result += f'''			<!--1 or more repetitions:-->\n'''
		for addressing_to in ([None] if ((not Header) or (not 'addressing_to' in Header)) else (Header['addressing_to'] if type(Header['addressing_to']) == list else [Header['addressing_to']])):
			result += f'''			<add:To>{addressing_to}</add:To>\n'''
		result += f'''			<add:From>\n'''
		for from_address in ([None] if ((not Header) or (not 'from_address' in Header)) else (Header['from_address'] if type(Header['from_address']) == list else [Header['from_address']])):
			result += f'''				<add:Address>{from_address}</add:Address>\n'''
		result += f'''			</add:From>\n'''
		result += f'''			<!--Optional:-->\n'''
		result += f'''			<add:ReplyTo>\n'''
		for reply_to_address in ([None] if ((not Header) or (not 'reply_to_address' in Header)) else (Header['reply_to_address'] if type(Header['reply_to_address']) == list else [Header['reply_to_address']])):
			result += f'''				<add:Address>{reply_to_address}</add:Address>\n'''
		result += f'''				<!--Optional:-->\n'''
		for service_name in ([None] if ((not Header) or (not 'service_name' in Header)) else (Header['service_name'] if type(Header['service_name']) == list else [Header['service_name']])):
			result += f'''				<add:ServiceName>{service_name}</add:ServiceName>\n'''
		result += f'''			</add:ReplyTo>\n'''
		for message_id in ([None] if ((not Header) or (not 'message_id' in Header)) else (Header['message_id'] if type(Header['message_id']) == list else [Header['message_id']])):
			result += f'''			<add:MessageID>{message_id}</add:MessageID>\n'''
		result += f'''		</add:Addressing>\n'''
		for Security in ([None] if ((not Header) or (not 'Security' in Header)) else (Header['Security'] if type(Header['Security']) == list else [Header['Security']])):
			result += f'''		<oas:Security>\n'''
			result += f'''			<wsu:Timestamp wsu:Id="string">\n'''
			for created in ([None] if ((not Security) or (not 'created' in Security)) else (Security['created'] if type(Security['created']) == list else [Security['created']])):
				result += f'''				<wsu:Created wsu:Id="string">{created}</wsu:Created>\n'''
			result += f'''				<!--Optional:-->\n'''
			for expires in ([None] if ((not Security) or (not 'expires' in Security)) else (Security['expires'] if type(Security['expires']) == list else [Security['expires']])):
				result += f'''				<wsu:Expires wsu:Id="string">{expires}</wsu:Expires>\n'''
			result += f'''			</wsu:Timestamp>\n'''
			result += f'''			<xd:Signature wsu:Id="string">\n'''
			result += f'''				<xd:SignedInfo wsu:Id="string">\n'''
			for CanonicalizationMethod in ([None] if ((not Security) or (not 'CanonicalizationMethod' in Security)) else (Security['CanonicalizationMethod'] if type(Security['CanonicalizationMethod']) == list else [Security['CanonicalizationMethod']])):
				result += f'''					<xd:CanonicalizationMethod xd1:Algorithm="http://www.w3.org/2010/xml-c14n2">\n'''
				for ignore_comments in ([None] if ((not CanonicalizationMethod) or (not 'ignore_comments' in CanonicalizationMethod)) else (CanonicalizationMethod['ignore_comments'] if type(CanonicalizationMethod['ignore_comments']) == list else [CanonicalizationMethod['ignore_comments']])):
					result += f'''						<x-:IgnoreComments>{ignore_comments}</x-:IgnoreComments>\n'''
				for trim_text_nodes in ([None] if ((not CanonicalizationMethod) or (not 'trim_text_nodes' in CanonicalizationMethod)) else (CanonicalizationMethod['trim_text_nodes'] if type(CanonicalizationMethod['trim_text_nodes']) == list else [CanonicalizationMethod['trim_text_nodes']])):
					result += f'''						<x-:TrimTextNodes>{trim_text_nodes}</x-:TrimTextNodes>\n'''
				for prefix_rewrite in ([None] if ((not CanonicalizationMethod) or (not 'prefix_rewrite' in CanonicalizationMethod)) else (CanonicalizationMethod['prefix_rewrite'] if type(CanonicalizationMethod['prefix_rewrite']) == list else [CanonicalizationMethod['prefix_rewrite']])):
					result += f'''						<x-:PrefixRewrite>{prefix_rewrite}</x-:PrefixRewrite>\n'''
				result += f'''						<x-:QNameAware>\n'''
				result += f'''							<!--You have a CHOICE of the next 4 items at this level-->\n'''
				if 'qname_aware_element' in CanonicalizationMethod:
					for qname_aware_element in ([None] if ((not CanonicalizationMethod) or (not 'qname_aware_element' in CanonicalizationMethod)) else (CanonicalizationMethod['qname_aware_element'] if type(CanonicalizationMethod['qname_aware_element']) == list else [CanonicalizationMethod['qname_aware_element']])):
						result += f'''							<x-:Element x-:Name="string" x-:NS="{qname_aware_element}"/>\n'''
				if 'qname_aware_xpath_element' in CanonicalizationMethod:
					for qname_aware_xpath_element in ([None] if ((not CanonicalizationMethod) or (not 'qname_aware_xpath_element' in CanonicalizationMethod)) else (CanonicalizationMethod['qname_aware_xpath_element'] if type(CanonicalizationMethod['qname_aware_xpath_element']) == list else [CanonicalizationMethod['qname_aware_xpath_element']])):
						result += f'''							<x-:XPathElement x-:Name="string" x-:NS="{qname_aware_xpath_element}"/>\n'''
				if 'qname_aware_qualified_attr' in CanonicalizationMethod:
					for qname_aware_qualified_attr in ([None] if ((not CanonicalizationMethod) or (not 'qname_aware_qualified_attr' in CanonicalizationMethod)) else (CanonicalizationMethod['qname_aware_qualified_attr'] if type(CanonicalizationMethod['qname_aware_qualified_attr']) == list else [CanonicalizationMethod['qname_aware_qualified_attr']])):
						result += f'''							<x-:QualifiedAttr x-:Name="string" x-:NS="{qname_aware_qualified_attr}"/>\n'''
				if 'qname_aware_unqualified_attr' in CanonicalizationMethod:
					for qname_aware_unqualified_attr in ([None] if ((not CanonicalizationMethod) or (not 'qname_aware_unqualified_attr' in CanonicalizationMethod)) else (CanonicalizationMethod['qname_aware_unqualified_attr'] if type(CanonicalizationMethod['qname_aware_unqualified_attr']) == list else [CanonicalizationMethod['qname_aware_unqualified_attr']])):
						result += f'''							<x-:UnqualifiedAttr x-:Name="string" x-:ParentName="string" x-:ParentNS="{qname_aware_unqualified_attr}"/>\n'''
				result += f'''						</x-:QNameAware>\n'''
				result += f'''					</xd:CanonicalizationMethod>\n'''
			result += f'''					<xd:SignatureMethod xd:Algorithm="urn:ietf:params:xml:ns:cpxmlsec:algorithms:gostr34102012-gostr34112012-512"/>\n'''
			result += f'''					<!--1 or more repetitions:-->\n'''
			for Reference in ([None] if ((not Security) or (not 'Reference' in Security)) else (Security['Reference'] if type(Security['Reference']) == list else [Security['Reference']])):
				result += f'''					<xd:Reference wsu:Id="string">\n'''
				result += f'''						<xd:Transforms>\n'''
				result += f'''							<xd:Transform xd:Algorithm="http://www.w3.org/2010/xmldsig2#transform">\n'''
				result += f'''								<xd1:Selection xd1:URI="http://www.test.com/gero/nimborum" xd1:Algorithm="http://www.w3.org/2010/xmldsig2#xml"/>\n'''
				result += f'''								<xd1:Canonicalization xd1:Algorithm="http://www.w3.org/2010/xml-c14n2">\n'''
				for ignore_comments in ([None] if ((not Reference) or (not 'ignore_comments' in Reference)) else (Reference['ignore_comments'] if type(Reference['ignore_comments']) == list else [Reference['ignore_comments']])):
					result += f'''									<x-:IgnoreComments>{ignore_comments}</x-:IgnoreComments>\n'''
				for trim_text_nodes in ([None] if ((not Reference) or (not 'trim_text_nodes' in Reference)) else (Reference['trim_text_nodes'] if type(Reference['trim_text_nodes']) == list else [Reference['trim_text_nodes']])):
					result += f'''									<x-:TrimTextNodes>{trim_text_nodes}</x-:TrimTextNodes>\n'''
				for prefix_rewrite in ([None] if ((not Reference) or (not 'prefix_rewrite' in Reference)) else (Reference['prefix_rewrite'] if type(Reference['prefix_rewrite']) == list else [Reference['prefix_rewrite']])):
					result += f'''									<x-:PrefixRewrite>{prefix_rewrite}</x-:PrefixRewrite>\n'''
				result += f'''									<x-:QNameAware>\n'''
				result += f'''										<!--You have a CHOICE of the next 4 items at this level-->\n'''
				if 'qname_aware_element' in Reference:
					for qname_aware_element in ([None] if ((not Reference) or (not 'qname_aware_element' in Reference)) else (Reference['qname_aware_element'] if type(Reference['qname_aware_element']) == list else [Reference['qname_aware_element']])):
						result += f'''										<x-:Element x-:Name="string" x-:NS="{qname_aware_element}"/>\n'''
				if 'qname_aware_xpath_element' in Reference:
					for qname_aware_xpath_element in ([None] if ((not Reference) or (not 'qname_aware_xpath_element' in Reference)) else (Reference['qname_aware_xpath_element'] if type(Reference['qname_aware_xpath_element']) == list else [Reference['qname_aware_xpath_element']])):
						result += f'''										<x-:XPathElement x-:Name="string" x-:NS="{qname_aware_xpath_element}"/>\n'''
				if 'qname_aware_qualified_attr' in Reference:
					for qname_aware_qualified_attr in ([None] if ((not Reference) or (not 'qname_aware_qualified_attr' in Reference)) else (Reference['qname_aware_qualified_attr'] if type(Reference['qname_aware_qualified_attr']) == list else [Reference['qname_aware_qualified_attr']])):
						result += f'''										<x-:QualifiedAttr x-:Name="string" x-:NS="{qname_aware_qualified_attr}"/>\n'''
				if 'qname_aware_unqualified_attr' in Reference:
					for qname_aware_unqualified_attr in ([None] if ((not Reference) or (not 'qname_aware_unqualified_attr' in Reference)) else (Reference['qname_aware_unqualified_attr'] if type(Reference['qname_aware_unqualified_attr']) == list else [Reference['qname_aware_unqualified_attr']])):
						result += f'''										<x-:UnqualifiedAttr x-:Name="string" x-:ParentName="string" x-:ParentNS="{qname_aware_unqualified_attr}"/>\n'''
				result += f'''									</x-:QNameAware>\n'''
				result += f'''								</xd1:Canonicalization>\n'''
				result += f'''								<xd1:Verifications>\n'''
				result += f'''									<xd1:Verification xd1:DigestDataLength="32"/>\n'''
				result += f'''								</xd1:Verifications>\n'''
				result += f'''							</xd:Transform>\n'''
				result += f'''						</xd:Transforms>\n'''
				if 'digest_method' in Reference:
					for digest_method in ([None] if ((not Reference) or (not 'digest_method' in Reference)) else (Reference['digest_method'] if type(Reference['digest_method']) == list else [Reference['digest_method']])):
						result += f'''						<xd:DigestMethod xd:Algorithm="{digest_method}"/>\n'''
				if 'digest_value' in Reference:
					for digest_value in ([None] if ((not Reference) or (not 'digest_value' in Reference)) else (Reference['digest_value'] if type(Reference['digest_value']) == list else [Reference['digest_value']])):
						result += f'''						<xd:DigestValue>{digest_value}</xd:DigestValue>\n'''
				result += f'''					</xd:Reference>\n'''
			result += f'''				</xd:SignedInfo>\n'''
			for signature_value in ([None] if ((not Security) or (not 'signature_value' in Security)) else (Security['signature_value'] if type(Security['signature_value']) == list else [Security['signature_value']])):
				result += f'''				<xd:SignatureValue>{signature_value}</xd:SignatureValue>\n'''
			result += f'''				<xd:KeyInfo wsu:Id="string">\n'''
			result += f'''					<xd:X509Data>\n'''
			for certificate in ([None] if ((not Security) or (not 'certificate' in Security)) else (Security['certificate'] if type(Security['certificate']) == list else [Security['certificate']])):
				result += f'''						<xd:X509Certificate>{certificate}</xd:X509Certificate>\n'''
			result += f'''					</xd:X509Data>\n'''
			result += f'''				</xd:KeyInfo>\n'''
			result += f'''			</xd:Signature>\n'''
			result += f'''			<!--Zero or more repetitions:-->\n'''
			for EncryptedKey in ([None] if ((not Security) or (not 'EncryptedKey' in Security)) else (Security['EncryptedKey'] if type(Security['EncryptedKey']) == list else [Security['EncryptedKey']])):
				result += f'''			<xe:EncryptedKey wsu:Id="string">\n'''
				for encryption_method in ([None] if ((not EncryptedKey) or (not 'encryption_method' in EncryptedKey)) else (EncryptedKey['encryption_method'] if type(EncryptedKey['encryption_method']) == list else [EncryptedKey['encryption_method']])):
					result += f'''				<xe:EncryptionMethod xe:Algorithm="{encryption_method}"/>\n'''
				result += f'''				<xe:KeyInfo wsu:Id="string">\n'''
				result += f'''					<xd:X509Data>\n'''
				result += f'''						<!--You have a CHOICE of the next 3 items at this level-->\n'''
				if 'x509_certificate' in EncryptedKey:
					for x509_certificate in ([None] if ((not EncryptedKey) or (not 'x509_certificate' in EncryptedKey)) else (EncryptedKey['x509_certificate'] if type(EncryptedKey['x509_certificate']) == list else [EncryptedKey['x509_certificate']])):
						result += f'''						<xd:X509Certificate>{x509_certificate}</xd:X509Certificate>\n'''
				if 'x509_ski' in EncryptedKey:
					for x509_ski in ([None] if ((not EncryptedKey) or (not 'x509_ski' in EncryptedKey)) else (EncryptedKey['x509_ski'] if type(EncryptedKey['x509_ski']) == list else [EncryptedKey['x509_ski']])):
						result += f'''						<xd:X509SKI>{x509_ski}</xd:X509SKI>\n'''
				for IssuerSerial in ([None] if ((not EncryptedKey) or (not 'IssuerSerial' in EncryptedKey)) else (EncryptedKey['IssuerSerial'] if type(EncryptedKey['IssuerSerial']) == list else [EncryptedKey['IssuerSerial']])):
					result += f'''						<xd:X509IssuerSerial>\n'''
					for name in ([None] if ((not IssuerSerial) or (not 'name' in IssuerSerial)) else (IssuerSerial['name'] if type(IssuerSerial['name']) == list else [IssuerSerial['name']])):
						result += f'''							<xd:X509IssuerName>{name}</xd:X509IssuerName>\n'''
					for serial in ([None] if ((not IssuerSerial) or (not 'serial' in IssuerSerial)) else (IssuerSerial['serial'] if type(IssuerSerial['serial']) == list else [IssuerSerial['serial']])):
						result += f'''							<xd:X509Serial>{serial}</xd:X509Serial>\n'''
					result += f'''						</xd:X509IssuerSerial>\n'''
				result += f'''					</xd:X509Data>\n'''
				result += f'''				</xe:KeyInfo>\n'''
				result += f'''				<xe:CipherData>\n'''
				if 'cipher_value' in EncryptedKey:
					for cipher_value in ([None] if ((not EncryptedKey) or (not 'cipher_value' in EncryptedKey)) else (EncryptedKey['cipher_value'] if type(EncryptedKey['cipher_value']) == list else [EncryptedKey['cipher_value']])):
						result += f'''					<xe:CipherValue>{cipher_value}</xe:CipherValue>\n'''
				result += f'''				</xe:CipherData>\n'''
				result += f'''				<xe:ReferenceList>\n'''
				result += f'''					<!--1 or more repetitions:-->\n'''
				for DataReference in ([None] if ((not EncryptedKey) or (not 'DataReference' in EncryptedKey)) else (EncryptedKey['DataReference'] if type(EncryptedKey['DataReference']) == list else [EncryptedKey['DataReference']])):
					for uri in ([None] if ((not DataReference) or (not 'uri' in DataReference)) else (DataReference['uri'] if type(DataReference['uri']) == list else [DataReference['uri']])):
						result += f'''					<xe:DataReference xe:URI="{uri}"/>\n'''
				result += f'''				</xe:ReferenceList>\n'''
				result += f'''			</xe:EncryptedKey>\n'''
			result += f'''		</oas:Security>\n'''
		result += f'''	</soapenv:Header>\n'''
	result += f'''	<soapenv:Body wsu:Id="string">\n'''
	result += f'''		<soapenv:Notification>\n'''
	for notification_text in ([None] if ((not Notification) or (not 'notification_text' in Notification)) else (Notification['notification_text'] if type(Notification['notification_text']) == list else [Notification['notification_text']])):
		result += f'''			<not:Event>{notification_text}</not:Event>\n'''
	result += f'''		</soapenv:Notification>\n'''
	result += f'''	</soapenv:Body>\n'''
	result += f'''</soapenv:Envelope>\n'''
	return result
