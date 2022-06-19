int removeTemplate_(char *name) {

	Template *template = dictionaryLookup(_templates, name);
	if (template == NULL)
		return 1;
	
	free(template->text);
	
	treeRemove(_templates, name);

	return 0;

}


static PyObject *removeTemplate (
	PyObject *self,
	PyObject *args
) {

	char *name;
	
	if (!PyArg_ParseTuple(args, "s", &name))
		Py_RETURN_FALSE;

	if (removeTemplate_(name))
		Py_RETURN_FALSE;

	Py_RETURN_TRUE;

}