static PyObject *getTemplate (
	PyObject *self,
	PyObject *args
) {

	char *name;

	if (!PyArg_ParseTuple(args, "s", &name)) {
		return NULL;
	}

	Template *template = dictionaryLookup(_templates, name);
	if (template == NULL) {
		char *message = malloc(sizeof(char) * (24 + strlen(name) + 1));
		sprintf(message, "No template with name '%s'", name);
		PyErr_SetString(PyExc_KeyError, message);
		return NULL;
	}
	char *source_text = template->text;
	size_t length = strlen(source_text) + 1;

	char *result = malloc(sizeof(char) * (length + 1));
	memcpy(result, source_text, length);

	return PyUnicode_FromStringAndSize(result, length - 1);

}