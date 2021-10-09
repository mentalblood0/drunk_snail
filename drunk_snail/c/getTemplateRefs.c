char** getTemplateRefs_(char *name) {

	Template *template = dictionaryLookup(_templates, name);
	if (template == NULL)
		return NULL;
	
	return template->refs;

}


static PyObject *getTemplateRefs (
	PyObject *self,
	PyObject *args
) {

	char *name;
	
	if (!PyArg_ParseTuple(args, "s", &name)) {
		return PyLong_FromLong(1);
	}

	char **result = getTemplateRefs_(name);
	if (result == NULL)
		return Py_None;
	
	PyObject *result_converted = PyList_New(0);
	for (; *result; ++result)
		PyList_Append(result_converted, PyUnicode_FromString(*result));

	return result_converted;

}