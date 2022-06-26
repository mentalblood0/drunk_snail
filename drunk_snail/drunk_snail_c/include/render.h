#pragma once


#include <Python.h>

#include "../modules/List/include/List.h"

#include "RenderResult.h"



PyObject *empty_dict;

void render_(
	RenderResult *render_result,
	char *template_name,
	size_t template_name_length,
	char **output_end,
	size_t depth,
	size_t *buffer_size,
	List *other,
	size_t subarrays_length,
	PyObject *params
);
PyObject *render (PyObject *self, PyObject *args);