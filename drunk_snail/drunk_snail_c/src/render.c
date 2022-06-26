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
	listSet(*other, depth, &((_line).tokens.other), alloc_error);\
	if (alloc_error) {\
		exit_render_();\
	}\
\
}


#define renderLine(_line) {\
\
	switch ((_line).action) {\
\
		case ACTION_PARAM:\
\
			param_values = PyDict_GetItemString(params, (_line).tokens.name.copy);\
			if (param_values) {\
				if ((_line).flags.strict || PyList_Check(param_values)) {\
					list_size = PyList_Size(param_values);\
					for (j = 0; j < list_size; j++) {\
						item = PyList_GetItem(param_values, j);\
						if (!PyUnicode_Check(item)) {\
							item = PyObject_Str(item);\
						}\
						value = PyUnicode_AsUTF8AndSize(item, &value_size);\
						render__param(\
							*output_end,\
							(_line).tokens.line.start, (_line).tokens.other.left.length,\
							value, value_size,\
							(_line).tokens.expression.end, (_line).tokens.other.right.length\
						);\
					}\
				} else {\
					if (!PyUnicode_Check(param_values)) {\
						item = PyObject_Str(param_values);\
					} else {\
						item = param_values;\
					}\
					value = PyUnicode_AsUTF8AndSize(item, &value_size);\
					render__param(\
						*output_end,\
						(_line).tokens.line.start, (_line).tokens.other.left.length,\
						value, value_size,\
						(_line).tokens.expression.end, (_line).tokens.other.right.length\
					);\
				}\
			} else if (!(_line).flags.optional) {\
				render__param(\
					*output_end,\
					(_line).tokens.line.start, (_line).tokens.other.left.length,\
					"", 0,\
					(_line).tokens.expression.end, (_line).tokens.other.right.length\
				);\
			}\
\
			break;\
\
		case ACTION_REF:\
\
			ref_values = PyDict_GetItemString(params, (_line).tokens.name.copy);\
\
			if (ref_values) {\
\
				addOther(_line);\
\
				if ((_line).flags.strict || PyList_Check(ref_values)) {\
					list_size = PyList_Size(ref_values);\
					for (j = 0; j < list_size; j++) {\
						render_(\
							render_result,\
							(_line).tokens.name.start,\
							(_line).tokens.name.length,\
							output_end,\
							depth + 1,\
							buffer_size,\
							other,\
							subarrays_length + (_line).tokens.other.left.length + (_line).tokens.other.right.length,\
							PyList_GetItem(ref_values, j)\
						);\
						if (!render_result->result) {\
							return;\
						}\
					}\
				} else {\
					render_(\
						render_result,\
						(_line).tokens.name.start,\
						(_line).tokens.name.length,\
						output_end,\
						depth + 1,\
						buffer_size,\
						other,\
						subarrays_length + (_line).tokens.other.left.length + (_line).tokens.other.right.length,\
						ref_values\
					);\
					if (!render_result->result) {\
						return;\
					}\
				}\
\
			} else if (!(_line).flags.optional) {\
\
				addOther(_line);\
\
				render_(\
					render_result,\
					(_line).tokens.name.start,\
					(_line).tokens.name.length,\
					output_end,\
					depth + 1,\
					buffer_size,\
					other,\
					subarrays_length + (_line).tokens.other.left.length + (_line).tokens.other.right.length,\
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
			render__empty(*output_end, (_line).tokens.line.start, (_line).tokens.line.end - (_line).tokens.line.start);\
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
	List *other,
	size_t subarrays_length,
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
	PyObject *param_values;
	PyObject *ref_values;
	PyObject *item;

	Line *line = NULL;

	size_t i;
	int alloc_error = 0;
	size_t required_buffer_size;

	Other *other_temp;

	size_t i_line;
	for (i_line = 0; i_line < template->lines.length; i_line++) {
		line = template->lines.start[i_line];
		renderLine(*line);
	}

	if (!depth) {
		**output_end = 0;
	}

};


#define exit_render {\
	PyErr_SetString(PyExc_MemoryError, "Out of RAM");\
	return NULL;\
}


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

	List other;
	int error = 0;
	listCreate(other, 16, error);
	if (error) {
		exit_render;
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
		0,
		params
	);

	size_t i;
	listShallowClear(other);

	if (!render_result.result) {
		if (render_result.message) {
			PyErr_SetString(PyExc_KeyError, render_result.message);
		} else {
			PyErr_SetString(PyExc_MemoryError, "Out of RAM");
		}
		return NULL;
	}

	return PyUnicode_FromStringAndSize(render_result.result, output_end-render_result.result);

}