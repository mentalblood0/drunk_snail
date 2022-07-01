#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "../modules/drunk_snail_c/include/removeTemplate.h"



PyObject *removeTemplate_python (PyObject *self, PyObject *args) {

	char *name;

	if (!PyArg_ParseTuple(args, "s", &name))
		return NULL;

	removeTemplate(name);

	Py_RETURN_NONE;

}