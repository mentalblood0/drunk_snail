#include <stdlib.h>
#include <Python.h>
#include <sys/types.h>

#include "List.h"
#include "Template.h"
#include "templates.h"
#include "prefix_tree.h"



void addTemplate_(char *name, char *text) {

	Template *template = malloc(sizeof(Template));

	size_t text_length = strlen(text) + 1;
	template->text = malloc(sizeof(char) * text_length);
	memcpy_s(template->text, text_length, text, text_length);

	template->length = text_length - 1;
	template->buffer_size = template->length;
	listCreate(template->render_states, 16);

	treeInsert(templates, name, template);

}


PyObject *addTemplate (
	PyObject *self,
	PyObject *args
) {

	char *name, *text;

	if (!PyArg_ParseTuple(args, "ss", &name, &text))
		return PyLong_FromLong(1);

	addTemplate_(name, text);

	Py_RETURN_NONE;

}