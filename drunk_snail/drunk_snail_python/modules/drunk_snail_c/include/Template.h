#pragma once

#include <stdbool.h>
#include <sys/types.h>

#include "../include/Line.h"
#include "../modules/List/include/List.h"



listDefine(Line, LineList);

typedef struct {

	char *text;
	size_t length;
	size_t buffer_size;

	LineList lines;

} Template;