#pragma once

#include <stdlib.h>



typedef struct {
	void **start;
	size_t length;
	size_t allocated;
} List;


#define listCreate(target, initial_length) {\
	target.start = malloc(sizeof(void*) * initial_length);\
	target.length = 0;\
	target.allocated = initial_length;\
}


#define listPush(target, element) {\
	if (target.length == target.allocated) {\
		target.allocated *= 2;\
		target.start = realloc(target.start, sizeof(void*) * target.allocated);\
	}\
	target.start[target.length] = element;\
	target.length += 1;\
}

#define listClear(target, i) {\
	for (i = 0; i < target.length; i++) {\
		free(target.start[i]);\
	}\
	free(target.start);\
}