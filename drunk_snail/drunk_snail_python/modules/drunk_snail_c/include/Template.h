#pragma once

#include <stdbool.h>
#include <sys/types.h>

#include "../modules/List/include/List.h"



typedef struct {

	char *text;
	size_t length;
	size_t buffer_size;

	List lines;

} Template;