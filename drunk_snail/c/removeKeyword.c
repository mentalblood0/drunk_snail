int removeKeyword_(Keywords *keywords, char *keyword) {

	char *value = dictionaryLookup(keywords->tree, keyword);
	if (value == NULL) {
		return 1;
	}
	free(keywords->data[(int)value[0]]); // value[0] is symbol (see addKeyword)
	keywords->data[(int)value[0]] = NULL;

	treeRemove(keywords->tree, keyword);

	return 0;

}


static PyObject *removeKeyword (
	PyObject *self,
	PyObject *args
) {

	char *keyword;
	
	if (!PyArg_ParseTuple(args, "s", &keyword)) {
		return PyLong_FromLong(1);
	}

	removeKeyword_(_keywords, keyword);

	return PyLong_FromLong(0);

}