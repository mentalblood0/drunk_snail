#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "../modules/drunk_snail_c/include/addTemplate.h"



PyObject *addTemplate_python (
	PyObject *self,
	PyObject *args
	) {

	char *name, *text;
	Py_ssize_t text_length;

	if (!PyArg_ParseTuple(args, "ss#", &name, &text, &text_length)) {
		return NULL;
	}

	parse_result result = addTemplate(name, text, (size_t)text_length);
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