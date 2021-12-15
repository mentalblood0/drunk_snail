static PyObject *getTemplateRefs (
	PyObject *self,
	PyObject *args
) {

	char *name;
	
	if (!PyArg_ParseTuple(args, "s", &name)) {
		return PyLong_FromLong(1);
	}

	Template *template = dictionaryLookup(_templates, name);
	if (template == NULL)
		Py_RETURN_NONE;
	
	PyObject *result_converted = PyList_New(0);
	int i = 0;
	for (i = 0; i < template->refs_number; ++i)
		PyList_Append(result_converted, PyUnicode_FromString(template->refs[i]));

	return result_converted;

}