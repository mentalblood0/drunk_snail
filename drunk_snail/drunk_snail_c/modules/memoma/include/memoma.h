#pragma once

#include <stdio.h>
#include <stdlib.h>



#define drunk_malloc(target, size) {\
	do {\
		target = malloc(size);\
	} while (target == NULL);\
}


#define drunk_realloc(target, size, temp) {\
	if (size) {\
		do {\
			temp = realloc(target, size);\
		} while (temp == NULL);\
		target = temp;\
	}\
}


#define drunk_realloc_with_shifted(target, size, temp, shifted) {\
	if (size) {\
		do {\
			temp = realloc(target, size);\
		} while (temp == NULL);\
		(shifted) = temp + ((shifted) - target);\
		target = temp;\
	}\
}


#define drunk_memcpy(target, source, length) {\
	if (length) {\
		memcpy(target, source, length);\
	}\
}