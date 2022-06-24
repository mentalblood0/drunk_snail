#include <stdlib.h>
#include <Python.h>

#include "../modules/List/include/List.h"
#include "../modules/prefix_tree/include/prefix_tree.h"

#include "../include/Line.h"
#include "../include/Template.h"
#include "../include/templates.h"



void removeTemplate_(char *name) {

	Template *template = dictionaryLookup(templates, name);
	if (template == NULL)
		return;

	free(template->text);
	size_t i;
	for (i = 0; i < template->lines.length; i++) {
		freeLine(*((Line*)(template->lines.start[i])));
	}
	listClear(template->lines, i);

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