#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
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

	size_t other_size = 16;
	Other **other = NULL;

	bool error = false;
	drunk_malloc_one(other, sizeof(Other*) * other_size, error);
	if (error) {
		PyErr_SetString(PyExc_MemoryError, "Out of RAM");
		return NULL;
	}

	char *output_end = NULL;

	render(
		&render_result,
		name,
		strlen(name),
		&output_end,
		0,
		NULL,
		&other,
		&other_size,
		0,
		0,
		params
	);

	free(other);

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