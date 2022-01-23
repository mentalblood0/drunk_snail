int removeKeywordByKeywords(Keywords *keywords, char *keyword) {

	char *value = dictionaryLookup(keywords->tree, keyword);
	if (value == NULL) {
		return 1;
	}

	char symbol = value[0];
	if (keywords->data[(int)symbol])
		free(keywords->data[(int)symbol]);
	keywords->data[(int)symbol] = NULL;

	treeRemove(keywords->tree, keyword);

	return 0;

}


int removeKeywordByTemplateName(char *template_name, char *keyword) {

	Template *template = dictionaryLookup(_templates, template_name);
	Keywords *keywords = template->keywords;

	return removeKeywordByKeywords(template->keywords, keyword);

}


static PyObject *removeKeyword (
	PyObject *self,
	PyObject *args
) {

	char *template_name, *keyword;
	
	if (!PyArg_ParseTuple(args, "ss", &template_name, &keyword)) {
		return PyLong_FromLong(1);
	}

	int result = removeKeywordByTemplateName(template_name, keyword);

	return PyLong_FromLong(result);

}