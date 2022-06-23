#include <stdlib.h>
#include <Python.h>

#include "../modules/List/include/List.h"
#include "../include/Template.h"
#include "../include/templates.h"
#include "../modules/prefix_tree/include/prefix_tree.h"



void removeTemplate_(char *name) {

	Template *template = dictionaryLookup(templates, name);
	if (template == NULL)
		return;

	free(template->text);
	size_t i;
	listClear(template->render_states, i);

	treeRemove(templates, name);

	return;

}


PyObject *removeTemplate (
	PyObject *self,
	PyObject *args
) {

	char *name;

	if (!PyArg_ParseTuple(args, "s", &name))
		return NULL;

	removeTemplate_(name);

	Py_RETURN_NONE;

}