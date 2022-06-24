#pragma once


#include <Python.h>

#include "../include/ParseResult.h"



void parse__(char *template_name, size_t template_name_length, size_t depth, ParseResult *error_message);
PyObject* parse_(char *name);
PyObject* parse (PyObject *self, PyObject *args);