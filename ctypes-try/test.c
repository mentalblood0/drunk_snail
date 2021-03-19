#include <stdio.h>
#include <stdlib.h>

struct Namespaces {
};

struct Canonicalization_method {
	struct Ignore_comments *ignore_comments;
	struct Trim_text_nodes *trim_text_nodes;
	struct Prefix_rewrite *prefix_rewrite;
	struct Qname_aware_element *qname_aware_element;
	struct Qname_aware_xpath_element *qname_aware_xpath_element;
	struct Qname_aware_qualified_attr *qname_aware_qualified_attr;
	struct Qname_aware_unqualified_attr *qname_aware_unqualified_attr;
};

struct Reference {
	struct Ignore_comments *ignore_comments;
	struct Trim_text_nodes *trim_text_nodes;
	struct Prefix_rewrite *prefix_rewrite;
	struct Qname_aware_element *qname_aware_element;
	struct Qname_aware_xpath_element *qname_aware_xpath_element;
	struct Qname_aware_qualified_attr *qname_aware_qualified_attr;
	struct Qname_aware_unqualified_attr *qname_aware_unqualified_attr;
	struct Digest_method *digest_method;
	struct Digest_value *digest_value;
};

struct Security {
	struct Created *created;
	struct Expires *expires;
	struct Canonicalization_method *canonicalization_method;
	struct Reference *reference;
	struct Signature_value *signature_value;
	struct Sertificate *sertificate;
	struct Encrypted_key *encrypted_key;
};

struct Header {
	struct Lifecycle_id *lifecycle_id;
	struct Addressing_to *addressing_to;
	struct From_address *from_address;
	struct Reply_to_address *reply_to_address;
	struct Service_name *service_name;
	struct Message_id *message_id;
	struct Security *security;
};

struct Params {
	struct Namespaces *namespaces;
	struct Header *header;
	struct Notification_text *notification_text;
};

int main(void) {
	
}

// struct simple_inner {
// 	char *a;
// };

// struct simple {
// 	char *a;
// 	int b;
// 	float c;
// 	struct simple *d;
// };

// void printSimpleStruct(struct simple *s) {
// 	printf("a = '%s'\n", s->a);
// 	printf("b = %d\n", s->b);
// 	printf("c = %f\n", s->c);
// 	if (s->d)
// 		printSimpleStruct(s->d);
// }