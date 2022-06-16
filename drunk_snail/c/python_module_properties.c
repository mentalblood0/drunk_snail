static PyMethodDef methods[] = {
	{
		"addTemplate",
		addTemplate,
		METH_VARARGS,
		"Add template in order to render or use in other templates rendering"
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
		"render",
		render,
		METH_VARARGS,
		"render"
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
	empty_dict = PyDict_New();

	return PyModule_Create(&drunk_snail_c_module);

}