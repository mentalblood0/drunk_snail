int removeKeywordByKeywords(Keywords *keywords, char *keyword) {

	char *value = dictionaryLookup(keywords->tree, keyword);
	if (value == NULL) {
		return 1;
	}

	int symbol = (int)value[0];
	if (keywords->data[symbol]) {
		free(keywords->data[symbol]->keyword);
		free(keywords->data[symbol]);
	}
	keywords->data[symbol] = NULL;

	treeRemove(keywords->tree, keyword);

	return 0;

}


int removeKeywordByTemplateName(char *template_name, char *keyword) {

	Template *template = dictionaryLookup(_templates, template_name);
	Keywords *keywords = template->keywords;

	return removeKeywordByKeywords(template->keywords, keyword);

}


int removeKeywordBySymbol(char *template_name, char symbol) {

	Template *template = dictionaryLookup(_templates, template_name);
	Keywords *keywords = template->keywords;

	if (template->keywords->data[(int)symbol] == NULL)
		return 0;
	
	char *keyword = template->keywords->data[(int)symbol]->keyword;
	return removeKeywordByKeywords(template->keywords, keyword);

}


static PyObject *removeKeyword (
	PyObject *self,
	PyObject *args
) {

	char *template_name, *symbol_string;
	
	if (!PyArg_ParseTuple(args, "ss", &template_name, &symbol_string)) {
		return PyLong_FromLong(1);
	}

	int result = removeKeywordBySymbol(template_name, symbol_string[0]);

	return PyLong_FromLong(result);

}