#include <stdio.h>
#include <Python.h>
#include <stdlib.h>
#include <sys/types.h>

#include "Template.h"
#include "templates.h"



PyObject *getTemplate (
	PyObject *self,
	PyObject *args
) {

	char *name;

	if (!PyArg_ParseTuple(args, "s", &name)) {
		return NULL;
	}

	Template *template = dictionaryLookup(templates, name);
	if (template == NULL) {
		size_t message_size = 24 + strlen(name) + 1;
		char *message = malloc(sizeof(char) * message_size);
		sprintf_s(message, 24 + strlen(name) + 1, "No template with name '%s'", name);
		PyErr_SetString(PyExc_KeyError, message);
		return NULL;
	}
	char *source_text = template->text;
	size_t length = strlen(source_text) + 1;

	char *result = malloc(sizeof(char) * (length + 1));
	memcpy_s(result, length, source_text, length);

	return PyUnicode_FromStringAndSize(result, length - 1);

}