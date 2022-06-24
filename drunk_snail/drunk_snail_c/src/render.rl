#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>
#include <Python.h>

#include "../modules/List/include/List.h"
#include "../include/Other.h"
#include "../include/Template.h"
#include "../include/templates.h"
#include "../modules/prefix_tree/include/prefix_tree.h"
#include "../include/RenderResult.h"
#include "../modules/memoma/include/memoma.h"



%%{
	machine render;
	write data;
}%%



render__empty {%
<*other[:depth].left+><LINE><*other[:depth].right->

%}

render__param {%
<*other[:depth].left+><OTHER_LEFT><ARG><OTHER_RIGHT><*other[:depth].right->

%}



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


#define renderLine(state) {\
\
	switch ((state).action) {\
\
		case ACTION_PARAM:\
\
			if ((state).tokens.name.end - (state).tokens.name.start + 1 > *name_buffer_size) {\
				*name_buffer_size = (state).tokens.name.end - (state).tokens.name.start + 1;\
				drunk_realloc_one_render_(*name_buffer, sizeof(char) * (*name_buffer_size), char_temp);\
			}\
			drunk_memcpy(*name_buffer, (state).tokens.name.start, (state).tokens.name.end - (state).tokens.name.start);\
			(*name_buffer)[(state).tokens.name.end - (state).tokens.name.start] = 0;\
\
			param_values = PyDict_GetItemString(params, *name_buffer);\
			if (param_values) {\
				if ((state).flags.strict || PyList_Check(param_values)) {\
					list_size = PyList_Size(param_values);\
					for (j = 0; j < list_size; j++) {\
						item = PyList_GetItem(param_values, j);\
						if (!PyUnicode_Check(item)) {\
							item = PyObject_Str(item);\
						}\
						value = PyUnicode_AsUTF8AndSize(item, &value_size);\
						render__param(\
							*output_end,\
							(state).tokens.line.start, (state).tokens.expression.start - (state).tokens.line.start,\
							value, value_size,\
							(state).tokens.expression.end, (state).tokens.line.end - (state).tokens.expression.end\
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
						(state).tokens.line.start, (state).tokens.expression.start - (state).tokens.line.start,\
						value, value_size,\
						(state).tokens.expression.end, (state).tokens.line.end - (state).tokens.expression.end\
					);\
				}\
			} else if (!(state).flags.optional) {\
				render__param(\
					*output_end,\
					(state).tokens.line.start, (state).tokens.expression.start - (state).tokens.line.start,\
					"", 0,\
					(state).tokens.expression.end, (state).tokens.line.end - (state).tokens.expression.end\
				);\
			}\
\
			break;\
\
		case ACTION_REF:\
\
			if (depth >= *other_size) {\
				*other_size = depth * 2;\
				drunk_realloc_one_render_(*other, sizeof(Other) * (*other_size), other_temp);\
			}\
			(*other)[depth].left.start = (state).tokens.line.start;\
			(*other)[depth].left.length = (state).tokens.expression.start - (state).tokens.line.start;\
			(*other)[depth].right.start = (state).tokens.expression.end;\
			(*other)[depth].right.length = (state).tokens.line.end - (state).tokens.expression.end;\
\
			if ((state).tokens.name.end - (state).tokens.name.start + 1 > *name_buffer_size) {\
				*name_buffer_size = (state).tokens.name.end - (state).tokens.name.start + 1;\
				drunk_realloc_one_render_(*name_buffer, sizeof(char) * (*name_buffer_size), char_temp);\
			}\
			drunk_memcpy(*name_buffer, (state).tokens.name.start, (state).tokens.name.end - (state).tokens.name.start);\
			(*name_buffer)[(state).tokens.name.end - (state).tokens.name.start] = 0;\
\
			ref_values = PyDict_GetItemString(params, *name_buffer);\
			if (ref_values) {\
				if ((state).flags.strict || PyList_Check(ref_values)) {\
					list_size = PyList_Size(ref_values);\
					for (j = 0; j < list_size; j++) {\
						render_(\
							render_result,\
							(state).tokens.name.start,\
							(state).tokens.name.end - (state).tokens.name.start,\
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
						if (!render_result->result) {\
							return;\
						}\
					}\
				} else {\
					render_(\
						render_result,\
						(state).tokens.name.start,\
						(state).tokens.name.end - (state).tokens.name.start,\
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
					if (!render_result->result) {\
						return;\
					}\
				}\
			} else if (!(state).flags.optional) {\
				render_(\
					render_result,\
					(state).tokens.name.start,\
					(state).tokens.name.end - (state).tokens.name.start,\
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
				if (!render_result->result) {\
					return;\
				}\
			}\
\
			break;\
\
		default:\
			render__empty(*output_end, (state).tokens.line.start, (state).tokens.line.end - (state).tokens.line.start);\
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
	Other **other,
	size_t *other_size,
	char **name_buffer,
	size_t *name_buffer_size,
	size_t subarrays_length,
	PyObject *params
)
{

	Template *template = dictionaryLookupUnterminated(templates, template_name, template_name_length);
	if (template == NULL) {
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

	RenderState *state = NULL;

	size_t i;
	int alloc_error = 0;
	size_t required_buffer_size;

	char *char_temp;
	Other *other_temp;

	if (template->render_states.length == 0) {

		char *p = template->text;
		char *pe = template->text + template->length;
		char *eof = pe;
		size_t cs;

		drunk_malloc_one_render_(state, sizeof(RenderState) * 1);
		resetRenderState(*state);

		%%{

			action action_start_line { state->tokens.line.start = p; }
			action action_end_line {

				state->tokens.line.end = p;
				listPush(template->render_states, state, alloc_error);
				if (alloc_error) {
					free(state);
					exit_render_();
				}

				verifyAction(*state);

				renderLine(*state);

				drunk_malloc_one_render_(state, sizeof(RenderState) * 1);
				resetRenderState(*state)

			}

			action action_param { state->action = ACTION_PARAM; }
			action action_ref { state->action = ACTION_REF; }
			action action_optional { state->flags.optional = true; }
			action action_strict { state->flags.strict = true; }

			action action_start_name { state->tokens.name.start = p; }
			action action_end_name { state->tokens.name.end = p; }

			action action_start_expression {
				if (!(state->tokens.expression.start && state->tokens.name.end))
					state->tokens.expression.start = p;
			}
			action action_end_expression { state->tokens.expression.end = p; }

			open = '<!--';
			close = '-->';

			delimeter = '\n';
			other = (any - delimeter)+;

			param = '(param)' %action_param;
			ref = '(ref)' %action_ref;
			type = param | ref;

			optional = '(optional)' %action_optional;
			strict = '(strict)' %action_strict;
			flag = optional | strict;

			prefix = flag* type flag*;
			name = ([a-zA-Z_][a-zA-Z_0-9]*) >action_start_name %action_end_name;

			expression = (open ' '* prefix name ' '* close) >action_start_expression %action_end_expression;

			line = (other? expression? other?) >action_start_line %action_end_line;

			template = (line delimeter)* (line - zlen)?;
			main := template;

			write init;
			write exec;

		}%%

		free(state);

	} else {

		size_t i_template = 0;
		for (i_template; i_template < template->render_states.length; i_template++) {
			state = template->render_states.start[i_template];
			renderLine(*state);
		}

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

	size_t other_size = 16;
	Other *other = NULL;

	size_t name_buffer_size = 128;
	char *name_buffer = NULL;

	int error = 0;
	drunk_malloc_one(other, sizeof(Other) * other_size, error);
	if (error) {
		exit_render;
	}
	drunk_malloc_one(name_buffer, sizeof(char) * name_buffer_size, error);
	if (error) {
		free(other);
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
		&other_size,
		&name_buffer,
		&name_buffer_size,
		0,
		params
	);

	free(other);
	free(name_buffer);

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