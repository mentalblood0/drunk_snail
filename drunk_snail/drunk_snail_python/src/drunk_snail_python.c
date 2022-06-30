#include <Python.h>

#include "../modules/drunk_snail_c/include/templates.h"

#include "../src/parse_python.h"
#include "../src/render_python.h"
#include "../src/addTemplate_python.h"
#include "../src/getTemplate_python.h"
#include "../src/removeTemplate_python.h"



PyMethodDef methods[6] = {
	{
		"addTemplate",
		addTemplate_python,
		METH_VARARGS,
		"Add template in order to render or use in other templates rendering"
	},
	{
		"getTemplate",
		getTemplate_python,
		METH_VARARGS,
		"Get template text by name"
	},
	{
		"removeTemplate",
		removeTemplate_python,
		METH_VARARGS,
		"Remove template by name"
	},
	{
		"render",
		render_python,
		METH_VARARGS,
		"Render parsed template"
	},
	{
		"parse",
		parse_python,
		METH_VARARGS,
		"Parse template"
	},
	{NULL, NULL, 0, NULL}
};

struct PyModuleDef drunk_snail_c_module = {
	PyModuleDef_HEAD_INIT,
	"drunk_snail_python",
	"Interface to drunk snail C library",
	-1,
	methods
};

PyMODINIT_FUNC PyInit_drunk_snail_python(void) {

	templates = createTree();
	if (!templates) {
		PyErr_SetString(PyExc_MemoryError, "Out of RAM");
		return NULL;
	}
	empty_dict = PyDict_New();

	return PyModule_Create(&drunk_snail_c_module);

}