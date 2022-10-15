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
	if (length != 0) {\
		if (length == 1) {\
			*target++ = *source;\
		} else if (length == 2) {\
			*((uint16_t *restrict)target)++ = *(uint16_t *restrict)source;\
		} else if (length <= 4) {\
			*(uint32_t *restrict)target = *(uint32_t *restrict)source;\
			target += length;\
		} else if (length <= 8) {\
			*(uint64_t *restrict)target = *(uint64_t *restrict)source;\
			target += length;\
		} else {\
			memcpy((uint64_t *restrict)target, (uint64_t *restrict)source, length);\
			target += length;\
		}\
	}\
}
