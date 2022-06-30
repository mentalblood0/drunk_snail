#include <Python.h>

#include "../modules/drunk_snail_c/include/parse.h"



PyObject* parse_python (
	PyObject *self,
	PyObject *args
) {

	char *name = NULL;
	if (!PyArg_ParseTuple(args, "s", &name)) {
		return NULL;
	}

	parse_result result = parse(name);
	if (result.code) {
		if (result.message) {
			PyErr_SetString(PyExc_KeyError, result.message);
		} else {
			PyErr_SetString(PyExc_MemoryError, "Out of RAM");
		}
		return NULL;
	}

	Py_RETURN_NONE;

}