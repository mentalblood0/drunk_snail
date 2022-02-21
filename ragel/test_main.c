#include "test.c"



int main(void) {

	char input[128] = 
	"<table>\n"
	"	<th><!-- (param)Head --></th>\n"
	"	<!-- (ref)Row -->\n"
	"<table>\n";

	printf("'%s'\n", input);

	test(input);

	return 0;
}