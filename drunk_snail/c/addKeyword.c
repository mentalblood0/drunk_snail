void addKeyword_(Keywords *keywords, char *keyword, char symbol) {

	char *value_to_insert = malloc(sizeof(char) * 2);
	value_to_insert[0] = symbol;
	value_to_insert[1] = 0;
	treeInsert(keywords->tree, keyword, value_to_insert);

	KeywordData *data = malloc(sizeof(KeywordData));
	data->last_inclusion = NULL;

	char *k = keyword;
	for (; *k; k++);
	data->length = (int)(k - keyword);
	data->last_symbol = *k;

	keywords->data[(int)symbol] = data;

}


static PyObject *addKeyword (
	PyObject *self,
	PyObject *args
) {

	char 
		*keyword, 
		*value;
	
	if (!PyArg_ParseTuple(args, "ss", &keyword, &value)) {
		return PyLong_FromLong(1);
	}

	addKeyword_(_keywords, keyword, value[0]);

	return PyLong_FromLong(0);

}