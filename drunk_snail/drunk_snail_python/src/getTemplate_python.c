#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "../modules/drunk_snail_c/include/getTemplate.h"



PyObject *getTemplate_python (
	PyObject *self,
	PyObject *args
) {

	char *name;

	if (!PyArg_ParseTuple(args, "s", &name)) {
		return NULL;
	}

	getTemplate_result result = getTemplate(name);
	if (result.text == NULL) {
		PyErr_SetString(PyExc_KeyError, name);
		return NULL;
	}

	return PyBytes_FromStringAndSize(result.text, result.length);

}