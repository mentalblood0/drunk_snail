#pragma once


#include <sys/types.h>



typedef struct {
	char *start;
	size_t length;
} Substring;

typedef struct {
	Substring left;
	Substring right;
} Other;