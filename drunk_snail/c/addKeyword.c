static PyObject *addKeyword (
	PyObject *self,
	PyObject *args
) {

	char 
		*template_name,
		*keyword, 
		*symbol;
	
	if (!PyArg_ParseTuple(args, "sss", &template_name, &keyword, &symbol)) {
		return PyLong_FromLong(1);
	}

	Template *template = dictionaryLookup(_templates, template_name);
	addKeywordByKeywords(template->keywords, keyword, symbol[0]);

	return PyLong_FromLong(0);

}