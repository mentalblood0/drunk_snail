static PyMethodDef methods[] = {
	{"addKeyword",		addKeyword,		METH_VARARGS,	"Add keyword in order to customize syntax"},
	{"removeKeyword",	removeKeyword,	METH_VARARGS,	"Remove keyword in order to customize syntax"},
	{"addTemplate",		addTemplate,	METH_VARARGS,	"Add template in order to compile or use in compiling of other templates"},
	{"compile",			compile,		METH_VARARGS,	"Compile added template"},
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
	
	return PyModule_Create(&drunk_snail_c_module);

}