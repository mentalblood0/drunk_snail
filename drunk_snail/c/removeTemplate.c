int removeTemplate_(char *name) {

	Template *template = dictionaryLookup(_templates, name);
	if (template == NULL)
		return 1;

	Keywords *keywords = template->keywords;
	
	clearTree(keywords->tree);
	
	int i = 0;
	for (i = 0; i < 128; i++)
		if (*(keywords->data + i) != NULL)
			free(*(keywords->data + i));

	free(keywords->data);

	clearRefs(template);
	free(template->refs);
	
	treeRemove(_templates, name);

	return 0;

}


static PyObject *removeTemplate (
	PyObject *self,
	PyObject *args
) {

	char *name;
	
	if (!PyArg_ParseTuple(args, "s", &name))
		return Py_False;

	if (removeTemplate_(name))
		return Py_False;

	return Py_True;

}