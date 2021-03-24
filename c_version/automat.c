#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum bool {
	false,
	true
} bool;

typedef struct Automat {
	int *S; // states
	int init_s;
	bool *X; // input alphabet
	char init_x; // initial symbol
	bool *Y; // output alphabet
	int (*g)(int, char); // transition function
	char (*l)(int, char); // output function
} Automat;

Automat* createAutomat(int *states, int init_s, char *X_string, char init_x, char *Y_string, int (*g)(int, char), char (*l)(int, char)) {
	Automat *a = malloc(sizeof(Automat));
	a->S = states;
	a->init_x = init_x;
	a->g = g;
	a->l = l;
	
	a->X = malloc(sizeof(bool) * 128);
	char *c = X_string; 
	for (; *c; c++, a->X[(int)*c] = true) {}

	a->Y = malloc(sizeof(bool) * 128);
	c = Y_string; 
	for (; *c; c++, a->Y[(int)*c] = true) {}

	return a;
}

#define processString_chunk_size 128

char* processString(char *input, Automat *a) {
	size_t chunk_size = sizeof(char) * processString_chunk_size;
	char *result = malloc(chunk_size);
	char *buf = malloc(chunk_size);
	int s = a->init_s;

	char *c = input;
	char *x = result;
	for (; *c; c++) {
		s = a->g(s, *c);
		x += strcpy(x, a->l(s, *c));
	}
	return result;
}

int main(void) {
	return 0;
}