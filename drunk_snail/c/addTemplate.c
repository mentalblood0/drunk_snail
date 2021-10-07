Tree *_templates;


typedef struct Template {
	char *text;
	Keywords *keywords;
} Template;


void addTemplate_(char *name, char *text) {
	
	Template *template = malloc(sizeof(Template));

	int text_length = strlen(text) + 1;
	template->text = malloc(sizeof(char) * text_length);
	strncpy(template->text, text, text_length);
	
	template->keywords = createKeywords(128);
	
	treeInsert(_templates, name, template);

}


static PyObject *addTemplate (
	PyObject *self,
	PyObject *args
) {

	char 
		*name, 
		*template;
	
	if (!PyArg_ParseTuple(args, "ss", &name, &template))
		return PyLong_FromLong(1);

	addTemplate_(name, template);

	return PyLong_FromLong(0);

}