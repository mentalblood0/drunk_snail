char* getTemplate_(char *name) {

	Template *template = dictionaryLookup(_templates, name);
	if (template == NULL)
		return NULL;
	
	char *source_text = template->text;
	size_t length = strlen(source_text) + 1;

	char *copied_text = malloc(sizeof(char) * (strlen(source_text) + 1));
	strncpy(copied_text, source_text, length);

	return copied_text;

}


static PyObject *getTemplate (
	PyObject *self,
	PyObject *args
) {

	char *name;
	
	if (!PyArg_ParseTuple(args, "s", &name)) {
		return PyLong_FromLong(1);
	}

	char *result = getTemplate_(name);
	if (result == NULL)
		return Py_None;

	return PyUnicode_FromString(result);

}