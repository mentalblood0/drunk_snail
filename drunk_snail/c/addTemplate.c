Tree *_templates;


typedef struct Template {

	char *text;
	size_t length;

} Template;


void addTemplate_(char *name, char *text) {
	
	Template *template = malloc(sizeof(Template));

	size_t text_length = strlen(text) + 1;
	template->text = malloc(sizeof(char) * text_length);
	memcpy(template->text, text, text_length);

	template->length = text_length - 1;
	
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