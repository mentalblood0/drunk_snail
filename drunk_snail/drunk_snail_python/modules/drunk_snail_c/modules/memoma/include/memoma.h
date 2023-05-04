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
	switch (length) {\
		case 0:\
			break;\
		case 1:\
			*target = *source;\
			target += 1;\
			break;\
		case 2:\
			*((uint16_t *restrict)target) = *(uint16_t *restrict)source;\
			target += 2;\
			break;\
		case 3:\
		case 4:\
			*(uint32_t *restrict)target = *(uint32_t *restrict)source;\
			target += length;\
			break;\
		case 5:\
		case 6:\
		case 7:\
		case 8:\
			*(uint64_t *restrict)target = *(uint64_t *restrict)source;\
			target += length;\
			break;\
		default:\
			memcpy((uint64_t *restrict)target, (uint64_t *restrict)source, length);\
			target += length;\
			break;\
	}\
}
