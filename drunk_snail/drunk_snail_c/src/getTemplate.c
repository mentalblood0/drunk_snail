#include <stdio.h>
#include <Python.h>
#include <stdlib.h>
#include <sys/types.h>

#include "../include/Template.h"
#include "../include/templates.h"



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
		if (!message) {
			PyErr_SetString(PyExc_MemoryError, "Out of RAM");
			return NULL;
		}
		sprintf_s(message, 24 + strlen(name) + 1, "No template with name '%s'", name);
		PyErr_SetString(PyExc_KeyError, message);
		return NULL;
	}

	return PyUnicode_FromStringAndSize(template->text, template->length);

}