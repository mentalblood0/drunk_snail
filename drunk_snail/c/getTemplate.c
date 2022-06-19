static PyObject *getTemplate (
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

	char *source_text = template->text;
	size_t length = strlen(source_text) + 1;

	char *result = malloc(sizeof(char) * (length + 1));
	memcpy(result, source_text, length);

	return PyUnicode_FromStringAndSize(result, length - 1);

}