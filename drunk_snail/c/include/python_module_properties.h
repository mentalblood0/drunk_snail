#pragma once


#include <Python.h>



PyMethodDef methods[5];
struct PyModuleDef drunk_snail_c_module;

PyMODINIT_FUNC PyInit_drunk_snail_c(void);