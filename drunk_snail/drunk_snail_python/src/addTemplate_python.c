#include <Python.h>

#include "../modules/drunk_snail_c/include/addTemplate.h"



PyObject *addTemplate_python (
	PyObject *self,
	PyObject *args
) {

	char *name, *text;

	if (!PyArg_ParseTuple(args, "ss", &name, &text)) {
		return NULL;
	}

	parse_result result = addTemplate(name, text);
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