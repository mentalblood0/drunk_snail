#pragma once


#define PY_SSIZE_T_CLEAN
#include <Python.h>



#define DRUNK_TYPE PyObject*

// should be able to be used as size_t
#define DRUNK_LIST_LENGTH_TYPE Py_ssize_t

// should be able to be used as size_t
#define DRUNK_STRING_LENGTH_TYPE Py_ssize_t


// DRUNK_TYPE DRUNK_PARAMS_GET_ITEM(DRUNK_TYPE params, char *key)
#define DRUNK_PARAMS_GET_ITEM(params, key) PyDict_GetItemString(params, key)


// bool DRUNK_IS_LIST(DRUNK_TYPE list)
#define DRUNK_IS_LIST(list) PyList_Check(list)

// DRUNK_LIST_LENGTH_TYPE DRUNK_LIST_GET_LENGTH(DRUNK_TYPE list)
#define DRUNK_LIST_GET_LENGTH(list) PyList_GET_SIZE(list)

// DRUNK_TYPE DRUNK_LIST_GET_ITEM(DRUNK_TYPE list, DRUNK_LIST_LENGTH_TYPE n)
#define DRUNK_LIST_GET_ITEM(list, n) PyList_GET_ITEM(list, n)

// char* DRUNK_AS_STRING_AND_LENGTH(DRUNK_TYPE s, DRUNK_STRING_LENGTH_TYPE *length_pointer)
#define DRUNK_AS_STRING_AND_LENGTH(s, target, length_pointer) PyBytes_AsStringAndSize(s, &(target), length_pointer)


DRUNK_TYPE empty_dict;
