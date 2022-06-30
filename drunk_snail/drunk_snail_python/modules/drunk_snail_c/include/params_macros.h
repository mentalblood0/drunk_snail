#pragma once


#include <Python.h>



#define DRUNK_PARAMS_TYPE PyObject*
#define DRUNK_LIST_TYPE PyObject*
#define DRUNK_LIST_LENGTH_TYPE Py_ssize_t
#define DRUNK_STRING_LENGTH_TYPE Py_ssize_t

#define DRUNK_PARAMS_GET_ITEM(params, key) PyDict_GetItemString(params, key)

#define DRUNK_IS_LIST(list) PyList_Check(list)
#define DRUNK_LIST_GET_LENGTH(list) PyList_GET_SIZE(list)
#define DRUNK_LIST_GET_ITEM(list, n) PyList_GET_ITEM(list, n)
#define DRUNK_AS_STRING_AND_LENGTH(something, length_pointer) PyUnicode_AsUTF8AndSize(something, length_pointer)
