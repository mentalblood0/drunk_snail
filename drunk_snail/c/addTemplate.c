Tree *_templates;


void addTemplate_(char *name, char *template, Tree *cache) {
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