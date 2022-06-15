void test_(PyObject *dict) {

	PyObject *rows = PyDict_GetItemString(dict, "Row");

	Py_ssize_t i = 0;
	Py_ssize_t j = 0;
	for (i = 0; i < PyList_Size(rows); i++) {
		
		PyObject *r = PyList_GetItem(rows, i);
		PyObject *cells = PyDict_GetItemString(r, "cell");

		for (j = 0; j < PyList_Size(cells); j++) {
			PyObject *c = PyList_GetItem(cells, j);
			// printf("%s ", PyUnicode_AsUTF8(c));
		}

		// printf("\n");

	}

}


static PyObject *test (
	PyObject *self,
	PyObject *args
) {
	
	PyObject *dict;

	if (!PyArg_ParseTuple(args, "O!", &PyDict_Type, &dict))
		return PyLong_FromLong(1);

	test_(dict);

	return PyLong_FromLong(0);

}