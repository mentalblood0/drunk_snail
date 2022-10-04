#pragma once

#include <stdio.h>
#include <stdlib.h>



#define drunk_malloc_one(target, size, alloc_error) {\
	target = malloc(size);\
	alloc_error = !target;\
}


#define drunk_realloc_one(target, size, temp, alloc_error) {\
	if (size) {\
		temp = realloc(target, size);\
		if (!temp) {\
			alloc_error = true;\
			free(target);\
			target = NULL;\
		} else {\
			target = temp;\
			alloc_error = false;\
		}\
	}\
}


#define drunk_realloc_with_shifted(target, size, temp, shifted, alloc_error) {\
	if (size) {\
		temp = realloc(target, size);\
		if (!temp) {\
			alloc_error = true;\
			free(target);\
			target = NULL;\
		} else {\
			shifted = temp + ((shifted) - target);\
			target = temp;\
		}\
	}\
}


#define drunk_memcpy(target, source, length) {\
	if (length) {\
		switch (length) {\
			case 1:\
				*(target) = *(source);\
				++target;\
				break;\
			default:\
				memcpy(target, source, length);\
				target += length;\
				break;\
		}\
	}\
}
