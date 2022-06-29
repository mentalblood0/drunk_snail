#include <stdio.h>
#include <Python.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>

#include "../modules/List/include/List.h"
#include "../modules/memoma/include/memoma.h"
#include "../modules/prefix_tree/include/prefix_tree.h"

#include "../include/Line.h"
#include "../include/Other.h"
#include "../include/Template.h"
#include "../include/templates.h"
#include "../include/print_macros.h"
#include "../include/RenderResult.h"



#define exit_render_() {\
	if (render_result->result) {\
		free(render_result->result);\
		render_result->result = NULL;\
	}\
	return;\
}


#define drunk_malloc_one_render_(target, size) {\
	target = malloc(size);\
	if (!target) {\
		exit_render_();\
	}\
}


#define drunk_realloc_one_render_(target, size, temp) {\
	if (size) {\
		temp = realloc(target, size);\
		if (!temp) {\
			exit_render_()\
		} else {\
			target = temp;\
		}\
	}\
}


#define addOther(_line) {\
\
	if (depth >= *other_size) {\
		*other_size = depth * 2;\
		drunk_realloc_one_render_(*other, sizeof(Other*) * (*other_size), other_temp);\
	}\
	(*other)[depth] = &((_line).other);\
\
}


#define renderParamList(_line) {\
	list_size = PyList_GET_SIZE(values);\
	for (j = 0; j < list_size; j++) {\
		value = PyUnicode_AsUTF8AndSize(PyList_GET_ITEM(values, j), &value_size);\
		render__param(\
			*output_end,\
			(_line).other.left.start, (_line).other.left.length,\
			value, value_size,\
			(_line).other.right.start, (_line).other.right.length\
		);\
	}\
}


#define renderRefList(_line) {\
	list_size = PyList_GET_SIZE(values);\
	for (j = 0; j < list_size; j++) {\
		render_(\
			render_result,\
			(_line).tokens.name.start,\
			(_line).tokens.name.length,\
			output_end,\
			depth + 1,\
			buffer_size,\
			other,\
			other_size,\
			other_left_length + (_line).other.left.length,\
			other_right_length + (_line).other.right.length,\
			PyList_GET_ITEM(values, j)\
		);\
		if (!render_result->result) {\
			return;\
		}\
	}\
}


#define renderLine(_line) {\
\
	switch ((_line).action) {\
\
		case ACTION_PARAM:\
\
			values = PyDict_GetItemString(params, (_line).tokens.name.copy);\
			if (values) {\
				if ((_line).flags.strict) {\
					renderParamList(_line);\
				} else if (PyList_Check(values)) {\
					renderParamList(_line);\
				} else {\
					value = PyUnicode_AsUTF8AndSize(values, &value_size);\
					render__param(\
						*output_end,\
						(_line).other.left.start, (_line).other.left.length,\
						value, value_size,\
						(_line).other.right.start, (_line).other.right.length\
					);\
				}\
			} else if (!(_line).flags.optional) {\
				render__param(\
					*output_end,\
					(_line).other.left.start, (_line).other.left.length,\
					"", 0,\
					(_line).other.right.start, (_line).other.right.length\
				);\
			}\
\
			break;\
\
		case ACTION_REF:\
\
			addOther(_line);\
\
			values = PyDict_GetItemString(params, (_line).tokens.name.copy);\
\
			if (values) {\
\
				if ((_line).flags.strict) {\
					renderRefList(_line);\
				} else if (PyList_Check(values)) {\
					renderRefList(_line);\
				} else {\
					render_(\
						render_result,\
						(_line).tokens.name.start,\
						(_line).tokens.name.length,\
						output_end,\
						depth + 1,\
						buffer_size,\
						other,\
						other_size,\
						other_left_length + (_line).other.left.length,\
						other_right_length + (_line).other.right.length,\
						values\
					);\
					if (!render_result->result) {\
						return;\
					}\
				}\
\
			} else if (!(_line).flags.optional) {\
\
				render_(\
					render_result,\
					(_line).tokens.name.start,\
					(_line).tokens.name.length,\
					output_end,\
					depth + 1,\
					buffer_size,\
					other,\
					other_size,\
					other_left_length + (_line).other.left.length,\
					other_right_length + (_line).other.right.length,\
					empty_dict\
				);\
				if (!render_result->result) {\
					return;\
				}\
\
			}\
\
			break;\
\
		default:\
			render__empty(*output_end, (_line).tokens.line.start, (_line).tokens.line.length);\
			break;\
\
	}\
\
}


PyObject *empty_dict;


void render_(
	RenderResult *render_result,
	char *template_name,
	size_t template_name_length,
	char **output_end,
	size_t depth,
	size_t *buffer_size,
	Other ***other,
	size_t *other_size,
	size_t other_left_length,
	size_t other_right_length,
	PyObject *params
)
{

	Template *template = dictionaryLookupUnterminated(templates, template_name, template_name_length);
	if ((template == NULL) || (!template->lines.length && template->length)) {
		if (render_result->result) {
			render_result->result = NULL;
		}
		drunk_malloc_one_render_(render_result->message, sizeof(char) * (template_name_length + 1));
		memcpy_s(render_result->message, template_name_length, template_name, template_name_length);
		render_result->message[template_name_length] = 0;
		return;
	}

	if (!render_result->result) {
		buffer_size = &template->buffer_size;
		drunk_malloc_one_render_(render_result->result, sizeof(char) * (*buffer_size));
		*output_end = render_result->result;
	}

	char *value;
	Py_ssize_t j;
	Py_ssize_t list_size;
	Py_ssize_t value_size;
	PyObject *values;

	Line *line = NULL;

	bool alloc_error = false;
	size_t i;
	size_t required_buffer_size;

	Other **other_temp;

	size_t i_line = 0;
	for (; i_line < template->lines.length; i_line++) {
		line = template->lines.start[i_line];
		renderLine(*line);
	}

};


PyObject *render (
	PyObject *self,
	PyObject *args
) {

	char *name = NULL;
	PyObject *params = NULL;

	if (!PyArg_ParseTuple(args, "sO!", &name, &PyDict_Type, &params))
		return NULL;

	RenderResult render_result;
	render_result.message = NULL;
	render_result.result = NULL;

	size_t other_size = 16;
	Other **other = NULL;

	bool error = false;
	drunk_malloc_one(other, sizeof(Other*) * other_size, error);
	if (error) {
		PyErr_SetString(PyExc_MemoryError, "Out of RAM");
		return NULL;
	}

	char *output_end = NULL;

	render_(
		&render_result,
		name,
		strlen(name),
		&output_end,
		0,
		NULL,
		&other,
		&other_size,
		0,
		0,
		params
	);

	free(other);

	if (!render_result.result) {
		if (render_result.message) {
			PyErr_SetString(PyExc_KeyError, render_result.message);
		} else {
			PyErr_SetString(PyExc_MemoryError, "Out of RAM");
		}
		return NULL;
	}

	PyObject *result = PyUnicode_FromStringAndSize(render_result.result, output_end-render_result.result);
	free(render_result.result);
	return result;

}