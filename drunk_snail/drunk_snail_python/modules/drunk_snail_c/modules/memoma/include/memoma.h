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
			case 2:\
				*(target) = *(source);\
				*(target+1) = *(source+1);\
				target += 2;\
				break;\
			case 4:\
				*(target) = *(source);\
				*(target+1) = *(source+1);\
				*(target+2) = *(source+2);\
				*(target+3) = *(source+3);\
				target += 4;\
				break;\
			default:\
				memcpy(target, source, length);\
				target += length;\
				break;\
		}\
	}\
}
