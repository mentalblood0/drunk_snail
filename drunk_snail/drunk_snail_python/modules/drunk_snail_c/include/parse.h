#pragma once


#include <sys/types.h>



typedef struct {
	int code;
	char *message;
} parse_result;


void _parse(
	char *template_name,
	size_t template_name_length,
	size_t depth,
	parse_result *parse_result
);

parse_result parse(char *name);