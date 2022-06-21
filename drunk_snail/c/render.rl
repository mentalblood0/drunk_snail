#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

%%{
	machine render;
	write data;
}%%



render__empty {%
<*other[:depth].left+><LINE><*other[:depth].right->

%}

render__arg {%
<OTHER_LEFT><ARG><OTHER_RIGHT>
%}

render__param {%
<*other[:depth].left+><render__arg><*other[:depth].right->

%}


typedef struct Substring {
	char *start;
	size_t length;
} Substring;


typedef struct Other {
	Substring left;
	Substring right;
} Other;


enum ActionType {
	ACTION_PARAM,
	ACTION_REF,
	ACTION_NONE
};


#define resetState(state) {\
	state.start_line = NULL;\
	state.end_line = NULL;\
	state.start_expression = NULL;\
	state.end_expression = NULL;\
	state.start_name = NULL;\
	state.end_name = NULL;\
	state.action_type = ACTION_NONE;\
	state.optional = false;\
	state.strict = false;\
}


typedef struct RenderResult {
	char *message;
	char *result;
} RenderResult;


#define ACTION_END_LINE(state) {\
\
	if ((state).end_name && (state).end_expression) {\
\
		if ((state).action_type == ACTION_PARAM) {\
\
			if ((state).end_name - (state).start_name + 1 > *name_buffer_size) {\
				*name_buffer_size = (state).end_name - (state).start_name + 1;\
				*name_buffer = realloc(*name_buffer, sizeof(char) * (*name_buffer_size));\
			}\
			memcpy(*name_buffer, (state).start_name, (state).end_name - (state).start_name);\
			(*name_buffer)[(state).end_name - (state).start_name] = 0;\
\
			param_values = PyDict_GetItemString(params, *name_buffer);\
			if (param_values) {\
				if ((state).strict || PyList_Check(param_values)) {\
					list_size = PyList_Size(param_values);\
					for (j = 0; j < list_size; j++) {\
						item = PyList_GetItem(param_values, j);\
						if (!PyUnicode_Check(item)) {\
							item = PyObject_Str(item);\
						}\
						value = PyUnicode_AsUTF8AndSize(\
							item,\
							&value_size\
						);\
						render__param(\
							output_end,\
							(state).start_line, (state).start_expression - (state).start_line,\
							value, value_size,\
							(state).end_expression, (state).end_line - (state).end_expression\
						);\
					}\
				} else {\
					if (!PyUnicode_Check(param_values)) {\
						item = PyObject_Str(param_values);\
					} else {\
						item = param_values;\
					}\
					value = PyUnicode_AsUTF8AndSize(\
						item,\
						&value_size\
					);\
					render__param(\
						output_end,\
						(state).start_line, (state).start_expression - (state).start_line,\
						value, value_size,\
						(state).end_expression, (state).end_line - (state).end_expression\
					);\
				}\
			} else if (!(state).optional) {\
				render__param(\
					output_end,\
					(state).start_line, (state).start_expression - (state).start_line,\
					"", 0,\
					(state).end_expression, (state).end_line - (state).end_expression\
				);\
			}\
\
		}\
		else if ((state).action_type == ACTION_REF) {\
\
			if (depth >= *other_size) {\
				*other_size = depth * 2;\
				*other = realloc(*other, sizeof(Other) * (*other_size));\
			}\
			(*other)[depth].left.start = (state).start_line;\
			(*other)[depth].left.length = (state).start_expression - (state).start_line;\
			(*other)[depth].right.start = (state).end_expression;\
			(*other)[depth].right.length = (state).end_line - (state).end_expression;\
\
			if ((state).end_name - (state).start_name + 1 > *name_buffer_size) {\
				*name_buffer_size = (state).end_name - (state).start_name + 1;\
				*name_buffer = realloc(*name_buffer, sizeof(char) * (*name_buffer_size));\
			}\
			memcpy(*name_buffer, (state).start_name, (state).end_name - (state).start_name);\
			(*name_buffer)[(state).end_name - (state).start_name] = 0;\
\
			ref_values = PyDict_GetItemString(params, *name_buffer);\
			if (ref_values) {\
				if ((state).strict || PyList_Check(ref_values)) {\
					list_size = PyList_Size(ref_values);\
					for (j = 0; j < list_size; j++) {\
						render_(\
							render_result,\
							(state).start_name,\
							(state).end_name - (state).start_name,\
							output_end,\
							depth + 1,\
							buffer_size,\
							other,\
							other_size,\
							name_buffer,\
							name_buffer_size,\
							subarrays_length + (*other)[depth].left.length + (*other)[depth].right.length,\
							PyList_GetItem(ref_values, j)\
						);\
					}\
				} else {\
					render_(\
						render_result,\
						(state).start_name,\
						(state).end_name - (state).start_name,\
						output_end,\
						depth + 1,\
						buffer_size,\
						other,\
						other_size,\
						name_buffer,\
						name_buffer_size,\
						subarrays_length + (*other)[depth].left.length + (*other)[depth].right.length,\
						ref_values\
					);\
				}\
			} else if (!(state).optional) {\
				render_(\
					render_result,\
					(state).start_name,\
					(state).end_name - (state).start_name,\
					output_end,\
					depth + 1,\
					buffer_size,\
					other,\
					other_size,\
					name_buffer,\
					name_buffer_size,\
					subarrays_length + (*other)[depth].left.length + (*other)[depth].right.length,\
					empty_dict\
				);\
			}\
\
		}\
\
	}\
\
	if ((state).action_type == ACTION_NONE) {\
		render__empty(output_end, (state).start_line, (state).end_line - (state).start_line);\
	}\
}


PyObject *empty_dict;


void render_(
	RenderResult *render_result,
	char *template_name,
	size_t template_name_length,
	char **output_end,
	size_t depth,
	size_t *buffer_size,
	Other **other,
	size_t *other_size,
	char **name_buffer,
	size_t *name_buffer_size,
	size_t subarrays_length,
	PyObject *params
)
{

	Template *template = dictionaryLookupUnterminated(_templates, template_name, template_name_length);
	if (template == NULL) {
		render_result->message = malloc(sizeof(char) * (template_name_length + 1));
		memcpy(render_result->message, template_name, template_name_length);
		render_result->message[template_name_length] = 0;
		return;
	}

	if (!depth) {
		buffer_size = &template->buffer_size;
		render_result->result = malloc(sizeof(char) * (*buffer_size));
		*output_end = render_result->result;
	}

	char *p = template->text;
	char *pe = template->text + template->length;
	char *eof = pe;
	size_t cs;
	char *new_result;
	char *value;
	Py_ssize_t value_size;
	PyObject *param_values;
	PyObject *ref_values;
	PyObject *item;

	size_t i;
	Py_ssize_t j;
	Py_ssize_t list_size;

	if (template->render_states == NULL) {

		RenderState state;
		resetState(state);

		%%{

			action action_start_line { state.start_line = p; }
			action action_end_line {
				state.end_line = p;
				addRenderState(template, state);
				ACTION_END_LINE(state);
				resetState(state);
			}

			action action_param { state.action_type = ACTION_PARAM; }
			action action_ref { state.action_type = ACTION_REF; }
			action action_optional { state.optional = true; }
			action action_strict { state.strict = true; }

			action action_start_name { state.start_name = p; }
			action action_end_name { state.end_name = p; }

			action action_start_expression {
				if (!(state.start_expression && state.end_name))
					state.start_expression = p;
			}
			action action_end_expression { state.end_expression = p; }

			open = '<!--';
			close = '-->';
			param = '(param)' %action_param;
			ref = '(ref)' %action_ref;
			optional = '(optional)' %action_optional;
			strict = '(strict)' %action_strict;

			delimeter = '\n';
			other = (any - delimeter)+;

			operator = param | ref | optional | strict;
			name = ([a-zA-Z_][a-zA-Z_0-9]*) >action_start_name %action_end_name;

			expression = (open ' '* operator+ name ' '* close) >action_start_expression %action_end_expression;

			line = (other? expression? other?) >action_start_line %action_end_line;

			template = (line delimeter)* (line - zlen)?;
			main := template;

			write init;
			write exec;

		}%%

	} else {

		RenderState *state;
		size_t i_template = 0;
		for (i_template = 0; i_template < template->render_states_current_size; i_template++) {
			state = template->render_states + i_template;
			ACTION_END_LINE(*state);
		}

	}

	if (!depth) {
		**output_end = 0;
	}

};


static PyObject *render (
	PyObject *self,
	PyObject *args
) {

	char *name;
	PyObject *params;

	if (!PyArg_ParseTuple(args, "sO!", &name, &PyDict_Type, &params))
		return NULL;

	RenderResult render_result;
	render_result.message = NULL;
	render_result.result = NULL;

	size_t other_size = 16;
	Other *other = malloc(sizeof(Other) * other_size);

	size_t name_buffer_size = 128;
	char *name_buffer = malloc(sizeof(char) * name_buffer_size);

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
		&name_buffer,
		&name_buffer_size,
		0,
		params
	);

	free(other);
	free(name_buffer);

	if (render_result.message) {
		free(render_result.result);
		PyErr_SetString(PyExc_KeyError, render_result.message);
		return NULL;
	}

	return PyUnicode_FromStringAndSize(render_result.result, output_end-render_result.result);

}