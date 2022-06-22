#include <stdlib.h>
#include <Python.h>

#include "List.h"
#include "Template.h"
#include "templates.h"
#include "prefix_tree.h"



int removeTemplate_(char *name) {

	Template *template = dictionaryLookup(templates, name);
	if (template == NULL)
		return 1;

	free(template->text);
	size_t i;
	listClear(template->render_states, i);

	treeRemove(templates, name);

	return 0;

}


PyObject *removeTemplate (
	PyObject *self,
	PyObject *args
) {

	char *name;

	if (!PyArg_ParseTuple(args, "s", &name))
		Py_RETURN_FALSE;

	if (removeTemplate_(name))
		Py_RETURN_FALSE;

	Py_RETURN_TRUE;

}