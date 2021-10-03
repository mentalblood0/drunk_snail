Tree *_templates;


typedef struct Template {
	char *text;
	Keywords *keywords;
} Template;


void addTemplate_(char *name, char *text, Tree *cache) {
	
	Template *template = malloc(sizeof(Template));

	char *t;
	for (t = text; *t; t++);
	int text_length = t - text + 1;

	template->text = malloc(sizeof(char) * text_length);
	int i = 0;
	for (i = 0; i < text_length; i++) {
		template->text[i] = text[i];
	}
	
	template->keywords = createDefaultKeywords();
	
	treeInsert(cache, name, template);

}


static PyObject *addTemplate (
	PyObject *self,
	PyObject *args
) {

	char 
		*name, 
		*template;
	
	if (!PyArg_ParseTuple(args, "ss", &name, &template)) {
		return PyLong_FromLong(1);
	}

	addTemplate_(name, template, _templates);

	return PyLong_FromLong(0);

}