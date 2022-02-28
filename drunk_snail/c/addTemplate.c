Tree *_templates;


typedef struct Template {

	char *text;
	size_t length;
	
	Keywords *keywords;
	
	char **refs;
	int refs_number;
	int refs_number_allocated;

} Template;


void addRef(Template *template, char *ref_start, size_t ref_length) {

	if (template->refs_number == template->refs_number_allocated) {
		template->refs_number_allocated *= 2;
		template->refs = realloc(template->refs, sizeof(char*) * template->refs_number_allocated);
	}

	template->refs[template->refs_number] = malloc(sizeof(char) * (ref_length + 1));
	strncpy(template->refs[template->refs_number], ref_start, (ref_length + 1));

	template->refs_number += 1;

}


void clearRefs(Template *template) {

	int i = 0;
	for (i = 0; i < template->refs_number; i++)
		if (template->refs[i]) {
			free(template->refs[i]);
			template->refs[i] = NULL;
		}

	template->refs_number = 0;

}


#define addTemplate__initial_refs_number_allocated 4

void addTemplate_(char *name, char *text) {
	
	Template *template = malloc(sizeof(Template));

	size_t text_length = strlen(text) + 1;
	template->text = malloc(sizeof(char) * text_length);
	strncpy(template->text, text, text_length);

	template->length = text_length - 1;
	
	template->keywords = createKeywords(128);

	template->refs = calloc(addTemplate__initial_refs_number_allocated, sizeof(char*));
	template->refs_number_allocated = addTemplate__initial_refs_number_allocated;
	template->refs_number = 0;
	
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