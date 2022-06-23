#include <stdio.h>
#include <Python.h>
#include <stdlib.h>
#include <sys/types.h>

#include "../include/Template.h"
#include "../include/templates.h"
#include "../modules/memoma/include/memoma.h"



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
	char *source_text = template->text;
	size_t length = template->length + 1;

	char *result = malloc(sizeof(char) * length);
	if (!result) {
		PyErr_SetString(PyExc_MemoryError, "Out of RAM");
		return NULL;
	}
	memcpy_s(result, length, source_text, length);

	return PyUnicode_FromStringAndSize(result, length - 1);

}