#include <Python.h>

#include "../include/render.h"
#include "../include/templates.h"
#include "../include/addTemplate.h"
#include "../include/getTemplate.h"
#include "../include/removeTemplate.h"



PyMethodDef methods[5] = {
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

struct PyModuleDef drunk_snail_c_module = {
	PyModuleDef_HEAD_INIT,
	"drunk_snail_c",
	"Interface to drunk_snail C library",
	-1,
	methods
};

PyMODINIT_FUNC PyInit_drunk_snail_c(void) {

	templates = createTree();
	empty_dict = PyDict_New();

	return PyModule_Create(&drunk_snail_c_module);

}