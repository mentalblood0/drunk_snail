#include "test.c"



int main(void) {

	char input[128] = "<table>\n\t<!-- (param)Row -->\n<table>\n<!-- (param) -->";
	printf("%s", input);
	// printf("input: ");
	// gets(input);

	test(input);

	return 0;
}