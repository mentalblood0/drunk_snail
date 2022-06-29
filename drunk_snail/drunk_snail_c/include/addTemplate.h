#pragma once


#include <stdbool.h>
#include <Python.h>



bool addTemplate_(char *name, char *text);
PyObject* addTemplate (PyObject *self, PyObject *args);