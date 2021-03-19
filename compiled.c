#include <stdio.h>
#include <stdlib.h>

struct CanonicalizationMethod {
	char **ignore_comments;
	char **trim_text_nodes;
	char **prefix_rewrite;
	char **qname_aware_element;
	char **qname_aware_xpath_element;
	char **qname_aware_qualified_attr;
	char **qname_aware_unqualified_attr;
};

struct Reference {
	char **ignore_comments;
	char **trim_text_nodes;
	char **prefix_rewrite;
	char **qname_aware_element;
	char **qname_aware_xpath_element;
	char **qname_aware_qualified_attr;
	char **qname_aware_unqualified_attr;
	char **digest_method;
	char **digest_value;
};

struct IssuerSerial {
	char **name;
	char **serial;
};

struct DataReference {
	char **uri;
};

struct EncryptedKey {
	char **encryption_method;
	char **x509_certificate;
	char **x509_ski;
	struct IssuerSerial *issuer_serial;
	char **cipher_value;
	struct DataReference *data_reference;
};

struct Security {
	char **created;
	char **expires;
	struct CanonicalizationMethod *canonicalization_method;
	struct Reference *reference;
	char **signature_value;
	char **certificate;
	struct EncryptedKey *encrypted_key;
};

struct Header {
	char **lifecycle_id;
	char **addressing_to;
	char **from_address;
	char **reply_to_address;
	char **service_name;
	char **message_id;
	struct Security *security;
};

struct Params {
	char **namespaces;
	struct Header *header;
	char **notification_text;
};

char* testFunction(struct Params *params) {
	char *result = (char*)malloc(sizeof(char) * 100000);
	char *result_end = result;
	result_end += sprintf(result_end, "<?xml version=\"1.0\"?>\n");
	struct namespaces* namespaces = params->namespaces;
	for (; *namespaces; namespaces++) {
		result_end += sprintf(result_end, "<soapenv:Envelope xmlns:soapenv=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:sch=\"http://xsd.gspvd/v001/schvr\" xmlns:wsu=\"http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-utility-1.0.xsd\" xmlns:add=\"http://xsd.gspvd/v001/addressing\" xmlns:xd=\"http://www.w3.org/2000/09/xmldsig#\" xmlns:xd1=\"http://www.w3.org/2010/xmldsig2#\" xmlns:x-=\"http://www.w3.org/2010/xml-c14n2\" xmlns:oas=\"http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-secext-1.0.xsd\" xmlns:xe=\"http://www.w3.org/2001/04/xmlenc#\" xmlns:prin=\"http://xsd.gspvd/v001/personalization/pc/print-tasks\" xmlns:com=\"http://xsd.gspvd/v001/personalization/request/common\" xmlns:com1=\"http://xsd.gspvd/v001/common-data\" xmlns:pas=\"http://xsd.gspvd/v001/personalization/request/passport\" xmlns:trav=\"http://xsd.gspvd/v001/personalization/request/travel-document\" xmlns:res=\"http://xsd.gspvd/v001/personalization/request/residence-permit\" xmlns:res1=\"http://xsd.gspvd/v001/personalization/response\" xmlns:req=\"http://xsd.gspvd/v001/personalization/request\" xmlns:form=\"http://xsd.gspvd/v001/forms/form\" xmlns:com2=\"http://xsd.gspvd/v001/forms/common\" xmlns:mat=\"http://xsd.gspvd/v001/forms/passport/mature\" xmlns:per=\"http://xsd.gspvd/v001/forms/internal/person-data-change\" xmlns:per1=\"http://xsd.gspvd/v001/forms/internal/person-address\" xmlns:con=\"http://xsd.gspvd/v001/forms/internal/control-info\" xmlns:per2=\"http://xsd.gspvd/v001/forms/internal/person-relatives\" xmlns:emp=\"http://xsd.gspvd/v001/forms/internal/employment-history\" xmlns:chil=\"http://xsd.gspvd/v001/forms/passport/child\" xmlns:ser=\"http://xsd.gspvd/v001/forms/passport/service-diplomatic\" xmlns:trav1=\"http://xsd.gspvd/v001/forms/travel-document\" xmlns:trav2=\"http://xsd.gspvd/v001/forms/travel-document-adult\" xmlns:trav3=\"http://xsd.gspvd/v001/forms/travel-document-adult-metrics\" xmlns:trav4=\"http://xsd.gspvd/v001/forms/travel-document-adult-biometrics\" xmlns:trav5=\"http://xsd.gspvd/v001/forms/travel-document-child\" xmlns:trav6=\"http://xsd.gspvd/v001/forms/travel-document-child-yml\" xmlns:trav7=\"http://xsd.gspvd/v001/forms/travel-document-child-metrics\" xmlns:res2=\"http://xsd.gspvd/v001/forms/residence-permit\" xmlns:pgs=\"http://xsd.gspvd/v001/forms/passport/pgs-child\" xmlns:pgs1=\"http://xsd.gspvd/v001/forms/passport/pgs-mature\" xmlns:res3=\"http://xsd.gspvd/v001/forms/residence-permit-adult-metrics-v1\" xmlns:res4=\"http://xsd.gspvd/v001/forms/residence-permit-adult-v1\" xmlns:res5=\"http://xsd.gspvd/v001/forms/residence-permit-child-incapable-metrics-v1\" xmlns:res6=\"http://xsd.gspvd/v001/forms/residence-permit-child-incapable-v1\" xmlns:res7=\"http://xsd.gspvd/v001/forms/residence-permit-replacement-metrics-v1\" xmlns:res8=\"http://xsd.gspvd/v001/forms/residence-permit-replacement-v1\" xmlns:res9=\"http://xsd.gspvd/v001/forms/residence-permit-duplicate-metrics-v1\" xmlns:res10=\"http://xsd.gspvd/v001/forms/residence-permit-duplicate-v1\" xmlns:res11=\"http://xsd.gspvd/v001/forms/residence-permit-correction-metrics-v1\" xmlns:res12=\"http://xsd.gspvd/v001/forms/residence-permit-correction-v1\" xmlns:faul=\"http://xsd.gspvd/v001/utility/faults\" xmlns:all=\"http://xsd.gspvd/v001/personalization/allowed\" xmlns:lif=\"http://xsd.gspvd/v001/lifecycle-state\" xmlns:res13=\"http://xsd.gspvd/v001/approvals/response\" xmlns:com3=\"http://xsd.gspvd/v001/approvals/common\" xmlns:req1=\"http://xsd.gspvd/v001/approvals/requisition\" xmlns:form1=\"http://xsd.gspvd/v001/approvals/form\" xmlns:cdb=\"http://xsd.gspvd/v001/approvals/cdb-response\" xmlns:req2=\"http://xsd.gspvd/v001/approvals/request\" xmlns:cdb1=\"http://xsd.gspvd/v001/approvals/cdb-request\" xmlns:not=\"http://xsd.gspvd/v001/utility/notification\" xmlns:dpc=\"http://xsd.gspvd/v001/personalization/pc/dpc-notifications\" xmlns:req3=\"http://xsd.gspvd/v001/GISMU/request\" xmlns:com4=\"http://xsd.gspvd/v001/GISMU/common-data\" xmlns:dos=\"http://xsd.gspvd/v001/GISMU/residence-permit/dossier\" xmlns:res14=\"http://xsd.gspvd/v001/GISMU/response\" xmlns:dos1=\"http://xsd.gspvd/v001/GISMU/refugee-travel/dossier\" xmlns:cdb2=\"http://xsd.gspvd/v001/cdb/cdb-type\" xmlns:cdb3=\"http://xsd.gspvd/v001/cdb/cdb-search-request\" xmlns:cdb4=\"http://xsd.gspvd/v001/cdb/cdb-search-response\" xmlns:cdb5=\"http://xsd.gspvd/v001/cdb/cdb-annul-request\" xmlns:cdb6=\"http://xsd.gspvd/v001/cdb/cdb-mrz-annul-request\" xmlns:cdb7=\"http://xsd.gspvd/v001/cdb/cdb-annul-response\" xmlns:cdb8=\"http://xsd.gspvd/v001/cdb/cdb-issuance-request\" xmlns:cdb9=\"http://xsd.gspvd/v001/cdb/cdb-issuance-response\" xmlns:arm=\"http://xsd.gspvd/v001/armus/armus-type\" xmlns:arm1=\"http://xsd.gspvd/v001/armus/armus-operations\" xmlns:arm2=\"http://xsd.gspvd/v001/armus/armus-common\" xmlns:fron=\"http://xsd.gspvd/v001/frontier-segment\" xmlns:req4=\"http://xsd.gspvd/v001/frontier-segment/border-intersection/request\" xmlns:res15=\"http://xsd.gspvd/v001/frontier-segment/border-intersection/response\" xmlns:fron1=\"http://xsd.gspvd/v001/GISMU/frontier-intersection\" xmlns:res16=\"http://xsd.gspvd/v001/frontier-segment/federal-inquiry/response\" xmlns:com5=\"http://xsd.gspvd/v001/frontier-segment/federal-inquiry/common\" xmlns:req5=\"http://xsd.gspvd/v001/frontier-segment/federal-inquiry/request\" xmlns:req6=\"http://xsd.gspvd/v001/frontier-segment/issued-document-data/request\" xmlns:req7=\"http://xsd.gspvd/v001/frontier-segment/invalid-document-data/request\" xmlns:fssp=\"http://xsd.gspvd/v001/frontier-segment/fssp-data\" xmlns:cer=\"http://xsd.gspvd/v001/certificate-order\" xmlns:cert=\"http://xsd.gspvd/v001/certificate-order/cert-order-form\" xmlns:cert1=\"http://xsd.gspvd/v001/certificate-order/cert-order-cms\" xmlns:cert2=\"http://xsd.gspvd/v001/certificate-order/cert-order-lifecycle-state\" xmlns:okz=\"http://xsd.gspvd/v001/okz-request\" xmlns:okz1=\"http://xsd.gspvd/v001/okz-request-ext\" xmlns:pkr=\"http://xsd.gspvd/v001/pkrbp/pkrbp\" xmlns:vs=\"http://xsd.gspvd/v001/vs\" xmlns:ns=\"urn://visa.xs.gosniias/1.0.1\" xmlns:pay=\"http://xsd.gspvd/v001/gisgmp/payment\" xmlns:ns1=\"urn://roskazna.ru/gisgmp/xsd/services/export-payments/2.1.1\" xmlns:ns2=\"http://roskazna.ru/gisgmp/xsd/SearchConditions/2.1.1\" xmlns:ns3=\"http://roskazna.ru/gisgmp/xsd/Common/2.1.1\" xmlns:typ=\"http://xsd.gspvd/v001/pgs/types\" xmlns:eac=\"http://xsd.gspvd/v001/eac\" xmlns:cert3=\"http://xsd.gspvd/v001/eac/cert-refs-request\" xmlns:cert4=\"http://xsd.gspvd/v001/eac/cert-request\" xmlns:cert5=\"http://xsd.gspvd/v001/eac/cert-response\" xmlns:mfc=\"http://xsd.gspvd/v001/mfc\" xmlns:ser1=\"http://xsd.gspvd/v001/utility/service\" xmlns:e=\"http://xsd.gspvd/v001/e-visa\" xmlns:fssp1=\"http://xsd.gspvd/v001/frontier-segment/fssp-data-async\" xmlns:bor=\"http://xsd.gspvd/v001/frontier-segment/border-intersection/bordercrossing\">\n");
	}
	struct Header* header = params->header;
	for (; *header; header++) {
		result_end += sprintf(result_end, "	<soapenv:Header>\n		<add:Addressing wsu:Id=\"AddressingHeader\">\n			<add:LifecycleInfo>\n");
		char** lifecycle_id = header->lifecycle_id;
		for (; *lifecycle_id; lifecycle_id++) {
			result_end += sprintf(result_end, "				<add:LifecycleID>%s</add:LifecycleID>\n", *lifecycle_id);
		}
		result_end += sprintf(result_end, "			</add:LifecycleInfo>\n			<!--1 or more repetitions:-->\n");
		char** addressing_to = header->addressing_to;
		for (; *addressing_to; addressing_to++) {
			result_end += sprintf(result_end, "			<add:To>%s</add:To>\n", *addressing_to);
		}
		result_end += sprintf(result_end, "			<add:From>\n");
		char** from_address = header->from_address;
		for (; *from_address; from_address++) {
			result_end += sprintf(result_end, "				<add:Address>%s</add:Address>\n", *from_address);
		}
		result_end += sprintf(result_end, "			</add:From>\n			<!--Optional:-->\n			<add:ReplyTo>\n");
		char** reply_to_address = header->reply_to_address;
		for (; *reply_to_address; reply_to_address++) {
			result_end += sprintf(result_end, "				<add:Address>%s</add:Address>\n", *reply_to_address);
		}
		result_end += sprintf(result_end, "				<!--Optional:-->\n");
		char** service_name = header->service_name;
		for (; *service_name; service_name++) {
			result_end += sprintf(result_end, "				<add:ServiceName>%s</add:ServiceName>\n", *service_name);
		}
		result_end += sprintf(result_end, "			</add:ReplyTo>\n");
		char** message_id = header->message_id;
		for (; *message_id; message_id++) {
			result_end += sprintf(result_end, "			<add:MessageID>%s</add:MessageID>\n", *message_id);
		}
		result_end += sprintf(result_end, "		</add:Addressing>\n");
		struct Security* security = header->security;
		for (; *security; security++) {
			result_end += sprintf(result_end, "		<oas:Security>\n			<wsu:Timestamp wsu:Id=\"string\">\n");
			char** created = security->created;
			for (; *created; created++) {
				result_end += sprintf(result_end, "				<wsu:Created wsu:Id=\"string\">%s</wsu:Created>\n", *created);
			}
			result_end += sprintf(result_end, "				<!--Optional:-->\n");
			char** expires = security->expires;
			for (; *expires; expires++) {
				result_end += sprintf(result_end, "				<wsu:Expires wsu:Id=\"string\">%s</wsu:Expires>\n", *expires);
			}
			result_end += sprintf(result_end, "			</wsu:Timestamp>\n			<xd:Signature wsu:Id=\"string\">\n				<xd:SignedInfo wsu:Id=\"string\">\n");
			struct CanonicalizationMethod* canonicalization_method = security->canonicalization_method;
			for (; *canonicalization_method; canonicalization_method++) {
				result_end += sprintf(result_end, "					<xd:CanonicalizationMethod xd1:Algorithm=\"http://www.w3.org/2010/xml-c14n2\">\n");
				char** ignore_comments = canonicalization_method->ignore_comments;
				for (; *ignore_comments; ignore_comments++) {
					result_end += sprintf(result_end, "						<x-:IgnoreComments>%s</x-:IgnoreComments>\n", *ignore_comments);
				}
				char** trim_text_nodes = canonicalization_method->trim_text_nodes;
				for (; *trim_text_nodes; trim_text_nodes++) {
					result_end += sprintf(result_end, "						<x-:TrimTextNodes>%s</x-:TrimTextNodes>\n", *trim_text_nodes);
				}
				char** prefix_rewrite = canonicalization_method->prefix_rewrite;
				for (; *prefix_rewrite; prefix_rewrite++) {
					result_end += sprintf(result_end, "						<x-:PrefixRewrite>%s</x-:PrefixRewrite>\n", *prefix_rewrite);
				}
				result_end += sprintf(result_end, "						<x-:QNameAware>\n							<!--You have a CHOICE of the next 4 items at this level-->\n");
				char** qname_aware_element = canonicalization_method->qname_aware_element;
				for (; *qname_aware_element; qname_aware_element++) {
					result_end += sprintf(result_end, "							<x-:Element x-:Name=\"string\" x-:NS=\"%s\"/>\n", *qname_aware_element);
				}
				char** qname_aware_xpath_element = canonicalization_method->qname_aware_xpath_element;
				for (; *qname_aware_xpath_element; qname_aware_xpath_element++) {
					result_end += sprintf(result_end, "							<x-:XPathElement x-:Name=\"string\" x-:NS=\"%s\"/>\n", *qname_aware_xpath_element);
				}
				char** qname_aware_qualified_attr = canonicalization_method->qname_aware_qualified_attr;
				for (; *qname_aware_qualified_attr; qname_aware_qualified_attr++) {
					result_end += sprintf(result_end, "							<x-:QualifiedAttr x-:Name=\"string\" x-:NS=\"%s\"/>\n", *qname_aware_qualified_attr);
				}
				char** qname_aware_unqualified_attr = canonicalization_method->qname_aware_unqualified_attr;
				for (; *qname_aware_unqualified_attr; qname_aware_unqualified_attr++) {
					result_end += sprintf(result_end, "							<x-:UnqualifiedAttr x-:Name=\"string\" x-:ParentName=\"string\" x-:ParentNS=\"%s\"/>\n", *qname_aware_unqualified_attr);
				}
				result_end += sprintf(result_end, "						</x-:QNameAware>\n					</xd:CanonicalizationMethod>\n");
			}
			result_end += sprintf(result_end, "					<xd:SignatureMethod xd:Algorithm=\"urn:ietf:params:xml:ns:cpxmlsec:algorithms:gostr34102012-gostr34112012-512\"/>\n					<!--1 or more repetitions:-->\n");
			struct Reference* reference = security->reference;
			for (; *reference; reference++) {
				result_end += sprintf(result_end, "					<xd:Reference wsu:Id=\"string\">\n						<xd:Transforms>\n							<xd:Transform xd:Algorithm=\"http://www.w3.org/2010/xmldsig2#transform\">\n								<xd1:Selection xd1:URI=\"http://www.test.com/gero/nimborum\" xd1:Algorithm=\"http://www.w3.org/2010/xmldsig2#xml\"/>\n								<xd1:Canonicalization xd1:Algorithm=\"http://www.w3.org/2010/xml-c14n2\">\n");
				char** ignore_comments = reference->ignore_comments;
				for (; *ignore_comments; ignore_comments++) {
					result_end += sprintf(result_end, "									<x-:IgnoreComments>%s</x-:IgnoreComments>\n", *ignore_comments);
				}
				char** trim_text_nodes = reference->trim_text_nodes;
				for (; *trim_text_nodes; trim_text_nodes++) {
					result_end += sprintf(result_end, "									<x-:TrimTextNodes>%s</x-:TrimTextNodes>\n", *trim_text_nodes);
				}
				char** prefix_rewrite = reference->prefix_rewrite;
				for (; *prefix_rewrite; prefix_rewrite++) {
					result_end += sprintf(result_end, "									<x-:PrefixRewrite>%s</x-:PrefixRewrite>\n", *prefix_rewrite);
				}
				result_end += sprintf(result_end, "									<x-:QNameAware>\n										<!--You have a CHOICE of the next 4 items at this level-->\n");
				char** qname_aware_element = reference->qname_aware_element;
				for (; *qname_aware_element; qname_aware_element++) {
					result_end += sprintf(result_end, "										<x-:Element x-:Name=\"string\" x-:NS=\"%s\"/>\n", *qname_aware_element);
				}
				char** qname_aware_xpath_element = reference->qname_aware_xpath_element;
				for (; *qname_aware_xpath_element; qname_aware_xpath_element++) {
					result_end += sprintf(result_end, "										<x-:XPathElement x-:Name=\"string\" x-:NS=\"%s\"/>\n", *qname_aware_xpath_element);
				}
				char** qname_aware_qualified_attr = reference->qname_aware_qualified_attr;
				for (; *qname_aware_qualified_attr; qname_aware_qualified_attr++) {
					result_end += sprintf(result_end, "										<x-:QualifiedAttr x-:Name=\"string\" x-:NS=\"%s\"/>\n", *qname_aware_qualified_attr);
				}
				char** qname_aware_unqualified_attr = reference->qname_aware_unqualified_attr;
				for (; *qname_aware_unqualified_attr; qname_aware_unqualified_attr++) {
					result_end += sprintf(result_end, "										<x-:UnqualifiedAttr x-:Name=\"string\" x-:ParentName=\"string\" x-:ParentNS=\"%s\"/>\n", *qname_aware_unqualified_attr);
				}
				result_end += sprintf(result_end, "									</x-:QNameAware>\n								</xd1:Canonicalization>\n								<xd1:Verifications>\n									<xd1:Verification xd1:DigestDataLength=\"32\"/>\n								</xd1:Verifications>\n							</xd:Transform>\n						</xd:Transforms>\n");
				char** digest_method = reference->digest_method;
				for (; *digest_method; digest_method++) {
					result_end += sprintf(result_end, "						<xd:DigestMethod xd:Algorithm=\"%s\"/>\n", *digest_method);
				}
				char** digest_value = reference->digest_value;
				for (; *digest_value; digest_value++) {
					result_end += sprintf(result_end, "						<xd:DigestValue>%s</xd:DigestValue>\n", *digest_value);
				}
				result_end += sprintf(result_end, "					</xd:Reference>\n");
			}
			result_end += sprintf(result_end, "				</xd:SignedInfo>\n");
			char** signature_value = security->signature_value;
			for (; *signature_value; signature_value++) {
				result_end += sprintf(result_end, "				<xd:SignatureValue>%s</xd:SignatureValue>\n", *signature_value);
			}
			result_end += sprintf(result_end, "				<xd:KeyInfo wsu:Id=\"string\">\n					<xd:X509Data>\n");
			char** certificate = security->certificate;
			for (; *certificate; certificate++) {
				result_end += sprintf(result_end, "						<xd:X509Certificate>%s</xd:X509Certificate>\n", *certificate);
			}
			result_end += sprintf(result_end, "					</xd:X509Data>\n				</xd:KeyInfo>\n			</xd:Signature>\n			<!--Zero or more repetitions:-->\n");
			struct EncryptedKey* encrypted_key = security->encrypted_key;
			for (; *encrypted_key; encrypted_key++) {
				result_end += sprintf(result_end, "			<xe:EncryptedKey wsu:Id=\"string\">\n");
				char** encryption_method = encrypted_key->encryption_method;
				for (; *encryption_method; encryption_method++) {
					result_end += sprintf(result_end, "				<xe:EncryptionMethod xe:Algorithm=\"%s\"/>\n", *encryption_method);
				}
				result_end += sprintf(result_end, "				<xe:KeyInfo wsu:Id=\"string\">\n					<xd:X509Data>\n						<!--You have a CHOICE of the next 3 items at this level-->\n");
				char** x509_certificate = encrypted_key->x509_certificate;
				for (; *x509_certificate; x509_certificate++) {
					result_end += sprintf(result_end, "						<xd:X509Certificate>%s</xd:X509Certificate>\n", *x509_certificate);
				}
				char** x509_ski = encrypted_key->x509_ski;
				for (; *x509_ski; x509_ski++) {
					result_end += sprintf(result_end, "						<xd:X509SKI>%s</xd:X509SKI>\n", *x509_ski);
				}
				struct IssuerSerial* issuer_serial = encrypted_key->issuer_serial;
				for (; *issuer_serial; issuer_serial++) {
					result_end += sprintf(result_end, "						<xd:X509IssuerSerial>\n");
					char** name = issuer_serial->name;
					for (; *name; name++) {
						result_end += sprintf(result_end, "							<xd:X509IssuerName>%s</xd:X509IssuerName>\n", *name);
					}
					char** serial = issuer_serial->serial;
					for (; *serial; serial++) {
						result_end += sprintf(result_end, "							<xd:X509Serial>%s</xd:X509Serial>\n", *serial);
					}
					result_end += sprintf(result_end, "						</xd:X509IssuerSerial>\n");
				}
				result_end += sprintf(result_end, "					</xd:X509Data>\n				</xe:KeyInfo>\n				<xe:CipherData>\n");
				char** cipher_value = encrypted_key->cipher_value;
				for (; *cipher_value; cipher_value++) {
					result_end += sprintf(result_end, "					<xe:CipherValue>%s</xe:CipherValue>\n", *cipher_value);
				}
				result_end += sprintf(result_end, "				</xe:CipherData>\n				<xe:ReferenceList>\n					<!--1 or more repetitions:-->\n");
				struct DataReference* data_reference = encrypted_key->data_reference;
				for (; *data_reference; data_reference++) {
					char** uri = data_reference->uri;
					for (; *uri; uri++) {
						result_end += sprintf(result_end, "					<xe:DataReference xe:URI=\"%s\"/>\n", *uri);
					}
				}
				result_end += sprintf(result_end, "				</xe:ReferenceList>\n			</xe:EncryptedKey>\n");
			}
			result_end += sprintf(result_end, "		</oas:Security>\n");
		}
		result_end += sprintf(result_end, "	</soapenv:Header>\n");
	}
	result_end += sprintf(result_end, "	<soapenv:Body wsu:Id=\"string\">\n		<soapenv:Notification>\n");
	char** notification_text = params->notification_text;
	for (; *notification_text; notification_text++) {
		result_end += sprintf(result_end, "			<not:Event>%s</not:Event>\n", *notification_text);
	}
	result_end += sprintf(result_end, "		</soapenv:Notification>\n	</soapenv:Body>\n</soapenv:Envelope>\n");
	return result;
}