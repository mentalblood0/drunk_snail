#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#define PY_SSIZE_T_CLEAN
#include <Python.h>



PyObject *render_hardcoded_python (PyObject *self, PyObject *args) {

	PyObject *params = NULL;

	if (!PyArg_ParseTuple(args, "O!", &PyDict_Type, &params))
		return NULL;

	char* result = malloc(sizeof(char) * 1024 * 256);
	char* output_end = result;
	Py_ssize_t content_size;
	char* content;

	memcpy(output_end, "<table>\n", 8); output_end += 8;

	PyObject* rows = PyDict_GetItemString(params, "Row");
	Py_ssize_t rows_count = PyList_GET_SIZE(rows);

	Py_ssize_t i, j;
	for (i = 0; i < rows_count; i++) {

		PyObject* r = PyList_GET_ITEM(rows, i);

		memcpy(output_end, "\t<tr>\n", 6); output_end += 6;

		PyObject* cells = PyDict_GetItemString(r, "cell");
		Py_ssize_t cells_count = PyList_GET_SIZE(cells);

		for (j = 0; j < cells_count; j++) {

			PyObject* c = PyList_GET_ITEM(cells, i);

			memcpy(output_end, "\t\t<td>", 6); output_end += 6;

			content = PyUnicode_AsUTF8AndSize(c, &content_size);
			memcpy(output_end, content, content_size);

			memcpy(output_end, "</td>\n", 6); output_end += 6;

		}

		memcpy(output_end, "\t</tr>\n", 7); output_end += 7;

	}

	memcpy(output_end, "</table>", 8); output_end += 8;

	PyObject *result_python = PyUnicode_FromStringAndSize(result, output_end - result);
	free(result);
	return result_python;

}