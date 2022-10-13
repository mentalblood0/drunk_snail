#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "../modules/drunk_snail_c/include/render.h"
#include "../modules/drunk_snail_c/modules/prefix_tree/include/prefix_tree.h"



PyObject *render_python (PyObject *self, PyObject *args) {

	char *name = NULL;
	PyObject *params = NULL;
	int detect_recursion = 0;

	if (!PyArg_ParseTuple(args, "sO|p", &name, &params, &detect_recursion))
		return NULL;

	RenderResult render_result;
	render_result.message = NULL;
	render_result.result = NULL;

	char *output_end = NULL;

	Tree *templates_stack = NULL;
	if (detect_recursion) {
		templates_stack = createTree();
	}

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
		params,
		templates_stack
	);

	if (templates_stack) {
		removeTree(templates_stack, false);
	}

	if (!render_result.result) {
		if (render_result.message) {
			PyErr_SetString(PyExc_KeyError, render_result.message);
		} else {
			PyErr_SetString(PyExc_MemoryError, "Out of RAM");
		}
		return NULL;
	}

	PyObject *result = PyBytes_FromStringAndSize(render_result.result, output_end-render_result.result);
	free(render_result.result);
	return result;

}