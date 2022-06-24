#include <stdlib.h>
#include <Python.h>
#include <sys/types.h>

#include "../include/parse.h"
#include "../include/Template.h"
#include "../include/templates.h"

#include "../modules/List/include/List.h"
#include "../modules/memoma/include/memoma.h"
#include "../modules/prefix_tree/include/prefix_tree.h"



int addTemplate_(char *name, char *text) {

	int error = 0;

	Template *template;
	drunk_malloc_one(template, sizeof(Template), error);
	if (error) {
		return error;
	}

	size_t text_length = strlen(text) + 1;
	drunk_malloc_one(template->text, sizeof(char) * text_length, error);
	if (error) {
		free(template);
		return error;
	}
	memcpy_s(template->text, text_length, text, text_length);

	template->length = text_length - 1;
	template->buffer_size = template->length;
	listCreate(template->lines, 16, error);
	if (error) {
		free(template->text);
		free(template);
		return error;
	}

	error = treeInsert(templates, name, template);

	return error;

}


PyObject *addTemplate (
	PyObject *self,
	PyObject *args
) {

	char *name, *text;

	if (!PyArg_ParseTuple(args, "ss", &name, &text))
		return NULL;

	if (addTemplate_(name, text)) {
		PyErr_SetString(PyExc_MemoryError, "Out of RAM");
		return NULL;
	}

	return parse_(name);

}