#pragma once



typedef struct {
	char *text;
	size_t length;
} getTemplate_result;


getTemplate_result getTemplate(char *name);