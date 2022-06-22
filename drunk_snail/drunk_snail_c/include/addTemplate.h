#pragma once


#include <Python.h>



void addTemplate_(char *name, char *text);
PyObject* addTemplate (PyObject *self, PyObject *args);