#include "test_preprocessed.c"



int main(void) {

	char input[128] = 
	"<table>\n"
	"	<th><!-- (param)Head --></th>\n"
	"	<!-- (ref)Row -->\n"
	"<table>\n";

	// printf("'%s'\n", input);

	char *output = compile(input);
	puts(output);

	return 0;
}