#pragma once


#include <sys/types.h>

#include "../modules/List/include/List.h"



typedef struct {
	char *start;
	size_t length;
} Substring;

typedef struct {
	Substring left;
	Substring right;
} Other;

listDefine(Other*, OtherPointerList);