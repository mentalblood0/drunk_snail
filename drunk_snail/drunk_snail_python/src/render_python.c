#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "../modules/drunk_snail_c/include/render.h"



PyObject *render_python (PyObject *self, PyObject *args) {

	char *name = NULL;
	PyObject *params = NULL;

	if (!PyArg_ParseTuple(args, "sO!", &name, &PyDict_Type, &params))
		return NULL;

	RenderResult render_result;
	render_result.message = NULL;
	render_result.result = NULL;

	char *output_end = NULL;

	render(
		&render_result,
		name,
		strlen(name),
		&output_end,
		0,
		NULL,
		NULL,
		0,
		0,
		params
	);

	if (!render_result.result) {
		if (render_result.message) {
			PyErr_SetString(PyExc_KeyError, render_result.message);
		} else {
			PyErr_SetString(PyExc_MemoryError, "Out of RAM");
		}
		return NULL;
	}

	PyObject *result = PyUnicode_FromStringAndSize(render_result.result, output_end-render_result.result);
	free(render_result.result);
	return result;

}