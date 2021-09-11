static PyMethodDef methods[] = {
	{"addTemplate",	addTemplate,	METH_VARARGS,	"Add template in order to compile or use in compiling of other templates"},
	{"compile",		compile,		METH_VARARGS,	"Compile added template"},
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

	_keywords = createKeywordsData(128);	
	addKeyword(_keywords, "\n",			'n');
	addKeyword(_keywords, "<!--",		'o');
	addKeyword(_keywords, "-->",		'c');
	addKeyword(_keywords, "(param)",	'p');
	addKeyword(_keywords, "(ref)",		'r');
	addKeyword(_keywords, "(optional)",	'?');
	
	return PyModule_Create(&drunk_snail_c_module);

}