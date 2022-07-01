#pragma once


#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "../modules/drunk_snail_c/include/render.h"



PyObject *render_python (PyObject *self, PyObject *args);