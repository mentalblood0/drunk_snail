#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

%%{
	machine render;
	write data;
}%%



render__empty {%
<other[:depth].left+><LINE><other[:depth].right->

%}

render__arg {%
<OTHER_LEFT><ARG><OTHER_RIGHT>
%}

render__param {%
<other[:depth].left+><render__arg><other[:depth].right->

%}


typedef struct Substring {
	char *start;
	int length;
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


typedef struct RenderResult {
	char *message;
	char *result;
} RenderResult;


#define reset_line_properties() {\
	start_line = NULL;\
	end_line = NULL;\
	start_expression = NULL;\
	end_expression = NULL;\
	name_start = NULL;\
	name_end = NULL;\
	action_type = ACTION_NONE;\
	optional = false;\
	strict = false;\
}


PyObject *empty_dict;


void render_(
	RenderResult *render_result,
	char *template_name,
	int template_name_length,
	char **output_end,
	int depth,
	int *buffer_size,
	Other *other,
	int *other_size,
	char *name_buffer,
	int *name_buffer_size,
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

	char *p = template->text;
	char *pe = template->text + template->length;
	char *eof = pe;
	int cs;
	char *new_result;
	char *value;
	Py_ssize_t value_size;
	PyObject *param_values;
	PyObject *ref_values;
	PyObject *item;

	int i;
	Py_ssize_t j;
	Py_ssize_t list_size;

	enum ActionType action_type = ACTION_NONE;
	bool optional = false;
	bool strict = false;

	char *start_line, *end_line, *start_expression, *end_expression, *name_start, *name_end;
	reset_line_properties();

	%%{
	
		action action_start_line { start_line = p; }
		action action_end_line {

			end_line = p;

			if (name_end && end_expression) {

				if (action_type == ACTION_PARAM) {

					if (name_end - name_start + 1 > name_buffer_size) {
						*name_buffer_size = name_end - name_start + 1;
						name_buffer = realloc(name_buffer, sizeof(char) * (*name_buffer_size));
					}
					memcpy(name_buffer, name_start, name_end - name_start);
					name_buffer[name_end - name_start] = 0;

					param_values = PyDict_GetItemString(params, name_buffer);
					if (param_values) {
						if (strict || PyList_Check(param_values)) {
							list_size = PyList_Size(param_values);
							for (j = 0; j < list_size; j++) {
								item = PyList_GetItem(param_values, j);
								if (!PyUnicode_Check(item)) {
									item = PyObject_Str(item);
								}
								value = PyUnicode_AsUTF8AndSize(
									item,
									&value_size
								);
								render__param(
									output_end,
									start_line, start_expression - start_line,
									value, value_size,
									end_expression, end_line - end_expression
								);
							}
						} else {
							if (!PyUnicode_Check(param_values)) {
								item = PyObject_Str(param_values);
							} else {
								item = param_values;
							}
							value = PyUnicode_AsUTF8AndSize(
								item,
								&value_size
							);
							render__param(
								output_end,
								start_line, start_expression - start_line,
								value, value_size,
								end_expression, end_line - end_expression
							);
						}
					} else if (!optional) {
						render__param(
							output_end,
							start_line, start_expression - start_line,
							"", 0,
							end_expression, end_line - end_expression
						);
					}

				}
				else if (action_type == ACTION_REF) {

					if (depth >= *other_size) {
						*other_size *= 2;
						other = realloc(other, sizeof(other) * (*other_size));
					}
					other[depth].left.start = start_line;
					other[depth].left.length = start_expression - start_line;
					other[depth].right.start = end_expression;
					other[depth].right.length = end_line - end_expression;

					if (name_end - name_start + 1 > name_buffer_size) {
						*name_buffer_size = name_end - name_start + 1;
						name_buffer = realloc(name_buffer, sizeof(char) * (*name_buffer_size));
					}
					memcpy(name_buffer, name_start, name_end - name_start);
					name_buffer[name_end - name_start] = 0;

					ref_values = PyDict_GetItemString(params, name_buffer);
					if (ref_values) {
						if (strict || PyList_Check(ref_values)) {
							list_size = PyList_Size(ref_values);
							for (j = 0; j < list_size; j++) {
								render_(
									render_result,
									name_start,
									name_end - name_start,
									output_end,
									depth + 1,
									buffer_size,
									other,
									other_size,
									name_buffer,
									name_buffer_size,
									PyList_GetItem(ref_values, j)
								);
							}
						} else {
							render_(
								render_result,
								name_start,
								name_end - name_start,
								output_end,
								depth + 1,
								buffer_size,
								other,
								other_size,
								name_buffer,
								name_buffer_size,
								ref_values
							);
						}
					} else if (!optional) {
						render_(
							render_result,
							name_start,
							name_end - name_start,
							output_end,
							depth + 1,
							buffer_size,
							other,
							other_size,
							name_buffer,
							name_buffer_size,
							empty_dict
						);
					}

				}

			}

			if (action_type == ACTION_NONE) {
				render__empty(output_end, start_line, end_line - start_line);
			}

			reset_line_properties();

		}

		action action_param { action_type = ACTION_PARAM; }
		action action_ref { action_type = ACTION_REF; }
		action action_optional { optional = true; }
		action action_strict { strict = true; }

		action action_name_start { name_start = p; }
		action action_name_end { name_end = p; }

		action action_start_expression {
			if (!(start_expression && name_end))
				start_expression = p;
		}
		action action_end_expression { end_expression = p; }

		open = '<!--';
		close = '-->';
		param = '(param)' %action_param;
		ref = '(ref)' %action_ref;
		optional = '(optional)' %action_optional;
		strict = '(strict)' %action_strict;

		delimeter = '\n';
		other = (any - delimeter)+;

		operator = param | ref | optional | strict;
		name = ([a-zA-Z_][a-zA-Z_0-9]*) >action_name_start %action_name_end;

		expression = (open ' '* operator+ name ' '* close) >action_start_expression %action_end_expression;

		line = (other? expression? other?) >action_start_line %action_end_line;

		template = (line delimeter)* (line - zlen)?;
		main := template;

		write init;
		write exec;
	}%%

	if (!depth) {
		**output_end = 0;
	}
};


static PyObject *render (
	PyObject *self,
	PyObject *args
) {

	char *name;
	int buffer_size;
	PyObject *params;
	
	if (!PyArg_ParseTuple(args, "siO!", &name, &buffer_size, &PyDict_Type, &params))
		return NULL;

	RenderResult render_result;
	render_result.message = NULL;
	render_result.result = malloc(sizeof(char) * buffer_size);

	int other_size = 16;
	Other *other = malloc(sizeof(Other) * other_size);

	int name_buffer_size = 128;
	char *name_buffer = malloc(sizeof(char) * name_buffer_size);

	char *_output_end = render_result.result;

	render_(
		&render_result,
		name,
		strlen(name),
		&_output_end,
		0,
		&buffer_size,
		other,
		&other_size,
		name_buffer,
		&name_buffer_size,
		params
	);

	free(other);
	free(name_buffer);

	if (render_result.message) {
		free(render_result.result);
		PyErr_SetString(PyExc_KeyError, render_result.message);
		return NULL;
	}

	PyObject *t = PyTuple_New(2);
	PyTuple_SetItem(t, 0, PyUnicode_FromStringAndSize(render_result.result, _output_end-render_result.result));
	PyTuple_SetItem(t, 1, PyLong_FromLong(buffer_size));
	return t;

}