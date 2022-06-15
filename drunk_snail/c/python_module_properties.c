static PyMethodDef methods[] = {
	{
		"addTemplate",
		addTemplate,
		METH_VARARGS,
		"Add template in order to compile or use in compiling of other templates"
	},
	{
		"compile",
		compile,
		METH_VARARGS,
		"Compile added template"
	},
	{
		"getTemplate",
		getTemplate,
		METH_VARARGS,
		"Get template text by name"
	},
	{
		"getTemplateRefs",
		getTemplateRefs,
		METH_VARARGS,
		"Get template refs"
	},
	{
		"removeTemplate",
		removeTemplate,
		METH_VARARGS,
		"Remove template by name"
	},
	{
		"test",
		test,
		METH_VARARGS,
		"test"
	},
	{NULL, NULL, 0, NULL}
};

static struct PyModuleDef drunk_snail_c_module = {
	PyModuleDef_HEAD_INIT,
	"drunk_snail_c",
	"Interface to drunk_snail C library",
	-1,
	methods
};

PyMODINIT_FUNC PyInit_drunk_snail_c(void) {

	_templates = createTree();

	int i = 0;
	for (i = 0; i < 128; i++)
		chars_to_escape_check[i] = 0;

	char *c = NULL;
	for (c = chars_to_escape; *c; c += 2) {
		chars_to_escape_check[(int)(*c)+128] = *(c + 1);
	}

	return PyModule_Create(&drunk_snail_c_module);

}