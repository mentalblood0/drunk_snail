
/* #line 1 "compileComprehension_preprocessed.rl" */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>


/* #line 10 "compileComprehension.c" */
static const int render_start = 0;
static const int render_first_final = 0;
static const int render_error = -1;

static const int render_en_main = 0;


/* #line 9 "compileComprehension_preprocessed.rl" */




#define render__empty(target, LINE, LINE_length) {\
	while ((*target - render_result->result) + (LINE_length+1+1) + subarrays_length >= *buffer_size) {\
		(*buffer_size) *= 2;\
		new_result = (char*)realloc(render_result->result, sizeof(char) * (*buffer_size));\
		*target = new_result + (*target - render_result->result);\
		render_result->result = new_result;\
	}\
	for (i = 0; i < depth; i++) {\
		memcpy(*target, (*other)[i].left.start, (*other)[i].left.length); *target += (*other)[i].left.length;\
	}\
	memcpy(*target, LINE, LINE_length); *target += LINE_length;\
	for (i = depth-1; i >= 0; i--) {\
		memcpy(*target, (*other)[i].right.start, (*other)[i].right.length); *target += (*other)[i].right.length;\
	}\
	memcpy(*target, "\n", 1); *target += 1;\
};

#define render__arg(target, OTHER_LEFT, OTHER_LEFT_length, ARG, ARG_length, OTHER_RIGHT, OTHER_RIGHT_length) {\
	while ((*target - render_result->result) + (OTHER_LEFT_length+ARG_length+OTHER_RIGHT_length+1) + subarrays_length >= *buffer_size) {\
		(*buffer_size) *= 2;\
		new_result = (char*)realloc(render_result->result, sizeof(char) * (*buffer_size));\
		*target = new_result + (*target - render_result->result);\
		render_result->result = new_result;\
	}\
	memcpy(*target, OTHER_LEFT, OTHER_LEFT_length); *target += OTHER_LEFT_length;\
	memcpy(*target, ARG, ARG_length); *target += ARG_length;\
	memcpy(*target, OTHER_RIGHT, OTHER_RIGHT_length); *target += OTHER_RIGHT_length;\
};

#define render__param(target, OTHER_LEFT, OTHER_LEFT_length, ARG, ARG_length, OTHER_RIGHT, OTHER_RIGHT_length) {\
	while ((*target - render_result->result) + (OTHER_LEFT_length+ARG_length+OTHER_RIGHT_length+1+1) + subarrays_length >= *buffer_size) {\
		(*buffer_size) *= 2;\
		new_result = (char*)realloc(render_result->result, sizeof(char) * (*buffer_size));\
		*target = new_result + (*target - render_result->result);\
		render_result->result = new_result;\
	}\
	for (i = 0; i < depth; i++) {\
		memcpy(*target, (*other)[i].left.start, (*other)[i].left.length); *target += (*other)[i].left.length;\
	}\
	render__arg(target, OTHER_LEFT, OTHER_LEFT_length, ARG, ARG_length, OTHER_RIGHT, OTHER_RIGHT_length);\
	for (i = depth-1; i >= 0; i--) {\
		memcpy(*target, (*other)[i].right.start, (*other)[i].right.length); *target += (*other)[i].right.length;\
	}\
	memcpy(*target, "\n", 1); *target += 1;\
};


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


typedef struct RenderState {
	char *start_line;
	char *end_line;
	char *start_expression;
	char *end_expression;
	char *start_name;
	char *end_name;
	enum ActionType action_type;
	bool optional;
	bool strict;
} RenderState;


typedef struct RenderResult {
	char *message;
	char *result;
} RenderResult;


PyObject *empty_dict;


void render_(
	RenderResult *render_result,
	char *template_name,
	int template_name_length,
	char **output_end,
	int depth,
	size_t *buffer_size,
	Other **other,
	int *other_size,
	char **name_buffer,
	int *name_buffer_size,
	int subarrays_length,
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

	RenderState state;
	resetState(state);

	
/* #line 173 "compileComprehension.c" */
	{
	cs = render_start;
	}

/* #line 178 "compileComprehension.c" */
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr1:
/* #line 164 "compileComprehension_preprocessed.rl" */
	{ state.start_line = p; }
/* #line 165 "compileComprehension_preprocessed.rl" */
	{

			state.end_line = p;

			if (state.end_name && state.end_expression) {

				if (state.action_type == ACTION_PARAM) {

					if (state.end_name - state.start_name + 1 > *name_buffer_size) {
						*name_buffer_size = state.end_name - state.start_name + 1;
						*name_buffer = realloc(*name_buffer, sizeof(char) * (*name_buffer_size));
					}
					memcpy(*name_buffer, state.start_name, state.end_name - state.start_name);
					(*name_buffer)[state.end_name - state.start_name] = 0;

					param_values = PyDict_GetItemString(params, *name_buffer);
					if (param_values) {
						if (state.strict || PyList_Check(param_values)) {
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
									state.start_line, state.start_expression - state.start_line,
									value, value_size,
									state.end_expression, state.end_line - state.end_expression
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
								state.start_line, state.start_expression - state.start_line,
								value, value_size,
								state.end_expression, state.end_line - state.end_expression
							);
						}
					} else if (!state.optional) {
						render__param(
							output_end,
							state.start_line, state.start_expression - state.start_line,
							"", 0,
							state.end_expression, state.end_line - state.end_expression
						);
					}

				}
				else if (state.action_type == ACTION_REF) {

					if (depth >= *other_size) {
						*other_size = depth * 2;
						*other = realloc(*other, sizeof(Other) * (*other_size));
					}
					(*other)[depth].left.start = state.start_line;
					(*other)[depth].left.length = state.start_expression - state.start_line;
					(*other)[depth].right.start = state.end_expression;
					(*other)[depth].right.length = state.end_line - state.end_expression;

					if (state.end_name - state.start_name + 1 > *name_buffer_size) {
						*name_buffer_size = state.end_name - state.start_name + 1;
						*name_buffer = realloc(*name_buffer, sizeof(char) * (*name_buffer_size));
					}
					memcpy(*name_buffer, state.start_name, state.end_name - state.start_name);
					(*name_buffer)[state.end_name - state.start_name] = 0;

					ref_values = PyDict_GetItemString(params, *name_buffer);
					if (ref_values) {
						if (state.strict || PyList_Check(ref_values)) {
							list_size = PyList_Size(ref_values);
							for (j = 0; j < list_size; j++) {
								render_(
									render_result,
									state.start_name,
									state.end_name - state.start_name,
									output_end,
									depth + 1,
									buffer_size,
									other,
									other_size,
									name_buffer,
									name_buffer_size,
									subarrays_length + (*other)[depth].left.length + (*other)[depth].right.length,
									PyList_GetItem(ref_values, j)
								);
							}
						} else {
							render_(
								render_result,
								state.start_name,
								state.end_name - state.start_name,
								output_end,
								depth + 1,
								buffer_size,
								other,
								other_size,
								name_buffer,
								name_buffer_size,
								subarrays_length + (*other)[depth].left.length + (*other)[depth].right.length,
								ref_values
							);
						}
					} else if (!state.optional) {
						render_(
							render_result,
							state.start_name,
							state.end_name - state.start_name,
							output_end,
							depth + 1,
							buffer_size,
							other,
							other_size,
							name_buffer,
							name_buffer_size,
							subarrays_length + (*other)[depth].left.length + (*other)[depth].right.length,
							empty_dict
						);
					}

				}

			}

			if (state.action_type == ACTION_NONE) {
				render__empty(output_end, state.start_line, state.end_line - state.start_line);
			}

			resetState(state);

		}
	goto st0;
tr4:
/* #line 165 "compileComprehension_preprocessed.rl" */
	{

			state.end_line = p;

			if (state.end_name && state.end_expression) {

				if (state.action_type == ACTION_PARAM) {

					if (state.end_name - state.start_name + 1 > *name_buffer_size) {
						*name_buffer_size = state.end_name - state.start_name + 1;
						*name_buffer = realloc(*name_buffer, sizeof(char) * (*name_buffer_size));
					}
					memcpy(*name_buffer, state.start_name, state.end_name - state.start_name);
					(*name_buffer)[state.end_name - state.start_name] = 0;

					param_values = PyDict_GetItemString(params, *name_buffer);
					if (param_values) {
						if (state.strict || PyList_Check(param_values)) {
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
									state.start_line, state.start_expression - state.start_line,
									value, value_size,
									state.end_expression, state.end_line - state.end_expression
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
								state.start_line, state.start_expression - state.start_line,
								value, value_size,
								state.end_expression, state.end_line - state.end_expression
							);
						}
					} else if (!state.optional) {
						render__param(
							output_end,
							state.start_line, state.start_expression - state.start_line,
							"", 0,
							state.end_expression, state.end_line - state.end_expression
						);
					}

				}
				else if (state.action_type == ACTION_REF) {

					if (depth >= *other_size) {
						*other_size = depth * 2;
						*other = realloc(*other, sizeof(Other) * (*other_size));
					}
					(*other)[depth].left.start = state.start_line;
					(*other)[depth].left.length = state.start_expression - state.start_line;
					(*other)[depth].right.start = state.end_expression;
					(*other)[depth].right.length = state.end_line - state.end_expression;

					if (state.end_name - state.start_name + 1 > *name_buffer_size) {
						*name_buffer_size = state.end_name - state.start_name + 1;
						*name_buffer = realloc(*name_buffer, sizeof(char) * (*name_buffer_size));
					}
					memcpy(*name_buffer, state.start_name, state.end_name - state.start_name);
					(*name_buffer)[state.end_name - state.start_name] = 0;

					ref_values = PyDict_GetItemString(params, *name_buffer);
					if (ref_values) {
						if (state.strict || PyList_Check(ref_values)) {
							list_size = PyList_Size(ref_values);
							for (j = 0; j < list_size; j++) {
								render_(
									render_result,
									state.start_name,
									state.end_name - state.start_name,
									output_end,
									depth + 1,
									buffer_size,
									other,
									other_size,
									name_buffer,
									name_buffer_size,
									subarrays_length + (*other)[depth].left.length + (*other)[depth].right.length,
									PyList_GetItem(ref_values, j)
								);
							}
						} else {
							render_(
								render_result,
								state.start_name,
								state.end_name - state.start_name,
								output_end,
								depth + 1,
								buffer_size,
								other,
								other_size,
								name_buffer,
								name_buffer_size,
								subarrays_length + (*other)[depth].left.length + (*other)[depth].right.length,
								ref_values
							);
						}
					} else if (!state.optional) {
						render_(
							render_result,
							state.start_name,
							state.end_name - state.start_name,
							output_end,
							depth + 1,
							buffer_size,
							other,
							other_size,
							name_buffer,
							name_buffer_size,
							subarrays_length + (*other)[depth].left.length + (*other)[depth].right.length,
							empty_dict
						);
					}

				}

			}

			if (state.action_type == ACTION_NONE) {
				render__empty(output_end, state.start_line, state.end_line - state.start_line);
			}

			resetState(state);

		}
	goto st0;
tr32:
/* #line 322 "compileComprehension_preprocessed.rl" */
	{ state.end_expression = p; }
/* #line 165 "compileComprehension_preprocessed.rl" */
	{

			state.end_line = p;

			if (state.end_name && state.end_expression) {

				if (state.action_type == ACTION_PARAM) {

					if (state.end_name - state.start_name + 1 > *name_buffer_size) {
						*name_buffer_size = state.end_name - state.start_name + 1;
						*name_buffer = realloc(*name_buffer, sizeof(char) * (*name_buffer_size));
					}
					memcpy(*name_buffer, state.start_name, state.end_name - state.start_name);
					(*name_buffer)[state.end_name - state.start_name] = 0;

					param_values = PyDict_GetItemString(params, *name_buffer);
					if (param_values) {
						if (state.strict || PyList_Check(param_values)) {
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
									state.start_line, state.start_expression - state.start_line,
									value, value_size,
									state.end_expression, state.end_line - state.end_expression
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
								state.start_line, state.start_expression - state.start_line,
								value, value_size,
								state.end_expression, state.end_line - state.end_expression
							);
						}
					} else if (!state.optional) {
						render__param(
							output_end,
							state.start_line, state.start_expression - state.start_line,
							"", 0,
							state.end_expression, state.end_line - state.end_expression
						);
					}

				}
				else if (state.action_type == ACTION_REF) {

					if (depth >= *other_size) {
						*other_size = depth * 2;
						*other = realloc(*other, sizeof(Other) * (*other_size));
					}
					(*other)[depth].left.start = state.start_line;
					(*other)[depth].left.length = state.start_expression - state.start_line;
					(*other)[depth].right.start = state.end_expression;
					(*other)[depth].right.length = state.end_line - state.end_expression;

					if (state.end_name - state.start_name + 1 > *name_buffer_size) {
						*name_buffer_size = state.end_name - state.start_name + 1;
						*name_buffer = realloc(*name_buffer, sizeof(char) * (*name_buffer_size));
					}
					memcpy(*name_buffer, state.start_name, state.end_name - state.start_name);
					(*name_buffer)[state.end_name - state.start_name] = 0;

					ref_values = PyDict_GetItemString(params, *name_buffer);
					if (ref_values) {
						if (state.strict || PyList_Check(ref_values)) {
							list_size = PyList_Size(ref_values);
							for (j = 0; j < list_size; j++) {
								render_(
									render_result,
									state.start_name,
									state.end_name - state.start_name,
									output_end,
									depth + 1,
									buffer_size,
									other,
									other_size,
									name_buffer,
									name_buffer_size,
									subarrays_length + (*other)[depth].left.length + (*other)[depth].right.length,
									PyList_GetItem(ref_values, j)
								);
							}
						} else {
							render_(
								render_result,
								state.start_name,
								state.end_name - state.start_name,
								output_end,
								depth + 1,
								buffer_size,
								other,
								other_size,
								name_buffer,
								name_buffer_size,
								subarrays_length + (*other)[depth].left.length + (*other)[depth].right.length,
								ref_values
							);
						}
					} else if (!state.optional) {
						render_(
							render_result,
							state.start_name,
							state.end_name - state.start_name,
							output_end,
							depth + 1,
							buffer_size,
							other,
							other_size,
							name_buffer,
							name_buffer_size,
							subarrays_length + (*other)[depth].left.length + (*other)[depth].right.length,
							empty_dict
						);
					}

				}

			}

			if (state.action_type == ACTION_NONE) {
				render__empty(output_end, state.start_line, state.end_line - state.start_line);
			}

			resetState(state);

		}
	goto st0;
st0:
	if ( ++p == pe )
		goto _test_eof0;
case 0:
/* #line 633 "compileComprehension.c" */
	switch( (*p) ) {
		case 10: goto tr1;
		case 60: goto tr2;
	}
	goto tr0;
tr0:
/* #line 164 "compileComprehension_preprocessed.rl" */
	{ state.start_line = p; }
	goto st1;
tr31:
/* #line 322 "compileComprehension_preprocessed.rl" */
	{ state.end_expression = p; }
	goto st1;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
/* #line 651 "compileComprehension.c" */
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
	}
	goto st1;
tr2:
/* #line 164 "compileComprehension_preprocessed.rl" */
	{ state.start_line = p; }
/* #line 318 "compileComprehension_preprocessed.rl" */
	{
			if (!(state.start_expression && state.end_name))
				state.start_expression = p;
		}
	goto st2;
tr5:
/* #line 318 "compileComprehension_preprocessed.rl" */
	{
			if (!(state.start_expression && state.end_name))
				state.start_expression = p;
		}
	goto st2;
tr33:
/* #line 318 "compileComprehension_preprocessed.rl" */
	{
			if (!(state.start_expression && state.end_name))
				state.start_expression = p;
		}
/* #line 322 "compileComprehension_preprocessed.rl" */
	{ state.end_expression = p; }
	goto st2;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
/* #line 686 "compileComprehension.c" */
	switch( (*p) ) {
		case 10: goto tr4;
		case 33: goto st3;
		case 60: goto tr5;
	}
	goto st1;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
	switch( (*p) ) {
		case 10: goto tr4;
		case 45: goto st4;
		case 60: goto tr5;
	}
	goto st1;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
	switch( (*p) ) {
		case 10: goto tr4;
		case 45: goto st5;
		case 60: goto tr5;
	}
	goto st1;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
	switch( (*p) ) {
		case 10: goto tr4;
		case 32: goto st5;
		case 40: goto st6;
		case 60: goto tr5;
	}
	goto st1;
tr22:
/* #line 312 "compileComprehension_preprocessed.rl" */
	{ state.optional = true; }
	goto st6;
tr39:
/* #line 310 "compileComprehension_preprocessed.rl" */
	{ state.action_type = ACTION_PARAM; }
	goto st6;
tr44:
/* #line 311 "compileComprehension_preprocessed.rl" */
	{ state.action_type = ACTION_REF; }
	goto st6;
tr52:
/* #line 313 "compileComprehension_preprocessed.rl" */
	{ state.strict = true; }
	goto st6;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
/* #line 744 "compileComprehension.c" */
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 111: goto st7;
		case 112: goto st21;
		case 114: goto st27;
		case 115: goto st31;
	}
	goto st1;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 112: goto st8;
	}
	goto st1;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 116: goto st9;
	}
	goto st1;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 105: goto st10;
	}
	goto st1;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 111: goto st11;
	}
	goto st1;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 110: goto st12;
	}
	goto st1;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 97: goto st13;
	}
	goto st1;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 108: goto st14;
	}
	goto st1;
st14:
	if ( ++p == pe )
		goto _test_eof14;
case 14:
	switch( (*p) ) {
		case 10: goto tr4;
		case 41: goto st15;
		case 60: goto tr5;
	}
	goto st1;
st15:
	if ( ++p == pe )
		goto _test_eof15;
case 15:
	switch( (*p) ) {
		case 10: goto tr4;
		case 40: goto tr22;
		case 60: goto tr5;
		case 95: goto tr23;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr23;
	} else if ( (*p) >= 65 )
		goto tr23;
	goto st1;
tr23:
/* #line 312 "compileComprehension_preprocessed.rl" */
	{ state.optional = true; }
/* #line 315 "compileComprehension_preprocessed.rl" */
	{ state.start_name = p; }
	goto st16;
tr40:
/* #line 310 "compileComprehension_preprocessed.rl" */
	{ state.action_type = ACTION_PARAM; }
/* #line 315 "compileComprehension_preprocessed.rl" */
	{ state.start_name = p; }
	goto st16;
tr45:
/* #line 311 "compileComprehension_preprocessed.rl" */
	{ state.action_type = ACTION_REF; }
/* #line 315 "compileComprehension_preprocessed.rl" */
	{ state.start_name = p; }
	goto st16;
tr53:
/* #line 313 "compileComprehension_preprocessed.rl" */
	{ state.strict = true; }
/* #line 315 "compileComprehension_preprocessed.rl" */
	{ state.start_name = p; }
	goto st16;
st16:
	if ( ++p == pe )
		goto _test_eof16;
case 16:
/* #line 878 "compileComprehension.c" */
	switch( (*p) ) {
		case 10: goto tr4;
		case 32: goto tr24;
		case 45: goto tr25;
		case 60: goto tr5;
		case 95: goto st16;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st16;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st16;
	} else
		goto st16;
	goto st1;
tr24:
/* #line 316 "compileComprehension_preprocessed.rl" */
	{ state.end_name = p; }
	goto st17;
st17:
	if ( ++p == pe )
		goto _test_eof17;
case 17:
/* #line 903 "compileComprehension.c" */
	switch( (*p) ) {
		case 10: goto tr4;
		case 32: goto st17;
		case 45: goto st18;
		case 60: goto tr5;
	}
	goto st1;
tr25:
/* #line 316 "compileComprehension_preprocessed.rl" */
	{ state.end_name = p; }
	goto st18;
st18:
	if ( ++p == pe )
		goto _test_eof18;
case 18:
/* #line 919 "compileComprehension.c" */
	switch( (*p) ) {
		case 10: goto tr4;
		case 45: goto st19;
		case 60: goto tr5;
	}
	goto st1;
st19:
	if ( ++p == pe )
		goto _test_eof19;
case 19:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 62: goto st20;
	}
	goto st1;
st20:
	if ( ++p == pe )
		goto _test_eof20;
case 20:
	switch( (*p) ) {
		case 10: goto tr32;
		case 60: goto tr33;
	}
	goto tr31;
st21:
	if ( ++p == pe )
		goto _test_eof21;
case 21:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 97: goto st22;
	}
	goto st1;
st22:
	if ( ++p == pe )
		goto _test_eof22;
case 22:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 114: goto st23;
	}
	goto st1;
st23:
	if ( ++p == pe )
		goto _test_eof23;
case 23:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 97: goto st24;
	}
	goto st1;
st24:
	if ( ++p == pe )
		goto _test_eof24;
case 24:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 109: goto st25;
	}
	goto st1;
st25:
	if ( ++p == pe )
		goto _test_eof25;
case 25:
	switch( (*p) ) {
		case 10: goto tr4;
		case 41: goto st26;
		case 60: goto tr5;
	}
	goto st1;
st26:
	if ( ++p == pe )
		goto _test_eof26;
case 26:
	switch( (*p) ) {
		case 10: goto tr4;
		case 40: goto tr39;
		case 60: goto tr5;
		case 95: goto tr40;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr40;
	} else if ( (*p) >= 65 )
		goto tr40;
	goto st1;
st27:
	if ( ++p == pe )
		goto _test_eof27;
case 27:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 101: goto st28;
	}
	goto st1;
st28:
	if ( ++p == pe )
		goto _test_eof28;
case 28:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 102: goto st29;
	}
	goto st1;
st29:
	if ( ++p == pe )
		goto _test_eof29;
case 29:
	switch( (*p) ) {
		case 10: goto tr4;
		case 41: goto st30;
		case 60: goto tr5;
	}
	goto st1;
st30:
	if ( ++p == pe )
		goto _test_eof30;
case 30:
	switch( (*p) ) {
		case 10: goto tr4;
		case 40: goto tr44;
		case 60: goto tr5;
		case 95: goto tr45;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr45;
	} else if ( (*p) >= 65 )
		goto tr45;
	goto st1;
st31:
	if ( ++p == pe )
		goto _test_eof31;
case 31:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 116: goto st32;
	}
	goto st1;
st32:
	if ( ++p == pe )
		goto _test_eof32;
case 32:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 114: goto st33;
	}
	goto st1;
st33:
	if ( ++p == pe )
		goto _test_eof33;
case 33:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 105: goto st34;
	}
	goto st1;
st34:
	if ( ++p == pe )
		goto _test_eof34;
case 34:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 99: goto st35;
	}
	goto st1;
st35:
	if ( ++p == pe )
		goto _test_eof35;
case 35:
	switch( (*p) ) {
		case 10: goto tr4;
		case 60: goto tr5;
		case 116: goto st36;
	}
	goto st1;
st36:
	if ( ++p == pe )
		goto _test_eof36;
case 36:
	switch( (*p) ) {
		case 10: goto tr4;
		case 41: goto st37;
		case 60: goto tr5;
	}
	goto st1;
st37:
	if ( ++p == pe )
		goto _test_eof37;
case 37:
	switch( (*p) ) {
		case 10: goto tr4;
		case 40: goto tr52;
		case 60: goto tr5;
		case 95: goto tr53;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr53;
	} else if ( (*p) >= 65 )
		goto tr53;
	goto st1;
	}
	_test_eof0: cs = 0; goto _test_eof; 
	_test_eof1: cs = 1; goto _test_eof; 
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof7: cs = 7; goto _test_eof; 
	_test_eof8: cs = 8; goto _test_eof; 
	_test_eof9: cs = 9; goto _test_eof; 
	_test_eof10: cs = 10; goto _test_eof; 
	_test_eof11: cs = 11; goto _test_eof; 
	_test_eof12: cs = 12; goto _test_eof; 
	_test_eof13: cs = 13; goto _test_eof; 
	_test_eof14: cs = 14; goto _test_eof; 
	_test_eof15: cs = 15; goto _test_eof; 
	_test_eof16: cs = 16; goto _test_eof; 
	_test_eof17: cs = 17; goto _test_eof; 
	_test_eof18: cs = 18; goto _test_eof; 
	_test_eof19: cs = 19; goto _test_eof; 
	_test_eof20: cs = 20; goto _test_eof; 
	_test_eof21: cs = 21; goto _test_eof; 
	_test_eof22: cs = 22; goto _test_eof; 
	_test_eof23: cs = 23; goto _test_eof; 
	_test_eof24: cs = 24; goto _test_eof; 
	_test_eof25: cs = 25; goto _test_eof; 
	_test_eof26: cs = 26; goto _test_eof; 
	_test_eof27: cs = 27; goto _test_eof; 
	_test_eof28: cs = 28; goto _test_eof; 
	_test_eof29: cs = 29; goto _test_eof; 
	_test_eof30: cs = 30; goto _test_eof; 
	_test_eof31: cs = 31; goto _test_eof; 
	_test_eof32: cs = 32; goto _test_eof; 
	_test_eof33: cs = 33; goto _test_eof; 
	_test_eof34: cs = 34; goto _test_eof; 
	_test_eof35: cs = 35; goto _test_eof; 
	_test_eof36: cs = 36; goto _test_eof; 
	_test_eof37: cs = 37; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 1: 
	case 2: 
	case 3: 
	case 4: 
	case 5: 
	case 6: 
	case 7: 
	case 8: 
	case 9: 
	case 10: 
	case 11: 
	case 12: 
	case 13: 
	case 14: 
	case 15: 
	case 16: 
	case 17: 
	case 18: 
	case 19: 
	case 21: 
	case 22: 
	case 23: 
	case 24: 
	case 25: 
	case 26: 
	case 27: 
	case 28: 
	case 29: 
	case 30: 
	case 31: 
	case 32: 
	case 33: 
	case 34: 
	case 35: 
	case 36: 
	case 37: 
/* #line 165 "compileComprehension_preprocessed.rl" */
	{

			state.end_line = p;

			if (state.end_name && state.end_expression) {

				if (state.action_type == ACTION_PARAM) {

					if (state.end_name - state.start_name + 1 > *name_buffer_size) {
						*name_buffer_size = state.end_name - state.start_name + 1;
						*name_buffer = realloc(*name_buffer, sizeof(char) * (*name_buffer_size));
					}
					memcpy(*name_buffer, state.start_name, state.end_name - state.start_name);
					(*name_buffer)[state.end_name - state.start_name] = 0;

					param_values = PyDict_GetItemString(params, *name_buffer);
					if (param_values) {
						if (state.strict || PyList_Check(param_values)) {
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
									state.start_line, state.start_expression - state.start_line,
									value, value_size,
									state.end_expression, state.end_line - state.end_expression
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
								state.start_line, state.start_expression - state.start_line,
								value, value_size,
								state.end_expression, state.end_line - state.end_expression
							);
						}
					} else if (!state.optional) {
						render__param(
							output_end,
							state.start_line, state.start_expression - state.start_line,
							"", 0,
							state.end_expression, state.end_line - state.end_expression
						);
					}

				}
				else if (state.action_type == ACTION_REF) {

					if (depth >= *other_size) {
						*other_size = depth * 2;
						*other = realloc(*other, sizeof(Other) * (*other_size));
					}
					(*other)[depth].left.start = state.start_line;
					(*other)[depth].left.length = state.start_expression - state.start_line;
					(*other)[depth].right.start = state.end_expression;
					(*other)[depth].right.length = state.end_line - state.end_expression;

					if (state.end_name - state.start_name + 1 > *name_buffer_size) {
						*name_buffer_size = state.end_name - state.start_name + 1;
						*name_buffer = realloc(*name_buffer, sizeof(char) * (*name_buffer_size));
					}
					memcpy(*name_buffer, state.start_name, state.end_name - state.start_name);
					(*name_buffer)[state.end_name - state.start_name] = 0;

					ref_values = PyDict_GetItemString(params, *name_buffer);
					if (ref_values) {
						if (state.strict || PyList_Check(ref_values)) {
							list_size = PyList_Size(ref_values);
							for (j = 0; j < list_size; j++) {
								render_(
									render_result,
									state.start_name,
									state.end_name - state.start_name,
									output_end,
									depth + 1,
									buffer_size,
									other,
									other_size,
									name_buffer,
									name_buffer_size,
									subarrays_length + (*other)[depth].left.length + (*other)[depth].right.length,
									PyList_GetItem(ref_values, j)
								);
							}
						} else {
							render_(
								render_result,
								state.start_name,
								state.end_name - state.start_name,
								output_end,
								depth + 1,
								buffer_size,
								other,
								other_size,
								name_buffer,
								name_buffer_size,
								subarrays_length + (*other)[depth].left.length + (*other)[depth].right.length,
								ref_values
							);
						}
					} else if (!state.optional) {
						render_(
							render_result,
							state.start_name,
							state.end_name - state.start_name,
							output_end,
							depth + 1,
							buffer_size,
							other,
							other_size,
							name_buffer,
							name_buffer_size,
							subarrays_length + (*other)[depth].left.length + (*other)[depth].right.length,
							empty_dict
						);
					}

				}

			}

			if (state.action_type == ACTION_NONE) {
				render__empty(output_end, state.start_line, state.end_line - state.start_line);
			}

			resetState(state);

		}
	break;
	case 20: 
/* #line 322 "compileComprehension_preprocessed.rl" */
	{ state.end_expression = p; }
/* #line 165 "compileComprehension_preprocessed.rl" */
	{

			state.end_line = p;

			if (state.end_name && state.end_expression) {

				if (state.action_type == ACTION_PARAM) {

					if (state.end_name - state.start_name + 1 > *name_buffer_size) {
						*name_buffer_size = state.end_name - state.start_name + 1;
						*name_buffer = realloc(*name_buffer, sizeof(char) * (*name_buffer_size));
					}
					memcpy(*name_buffer, state.start_name, state.end_name - state.start_name);
					(*name_buffer)[state.end_name - state.start_name] = 0;

					param_values = PyDict_GetItemString(params, *name_buffer);
					if (param_values) {
						if (state.strict || PyList_Check(param_values)) {
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
									state.start_line, state.start_expression - state.start_line,
									value, value_size,
									state.end_expression, state.end_line - state.end_expression
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
								state.start_line, state.start_expression - state.start_line,
								value, value_size,
								state.end_expression, state.end_line - state.end_expression
							);
						}
					} else if (!state.optional) {
						render__param(
							output_end,
							state.start_line, state.start_expression - state.start_line,
							"", 0,
							state.end_expression, state.end_line - state.end_expression
						);
					}

				}
				else if (state.action_type == ACTION_REF) {

					if (depth >= *other_size) {
						*other_size = depth * 2;
						*other = realloc(*other, sizeof(Other) * (*other_size));
					}
					(*other)[depth].left.start = state.start_line;
					(*other)[depth].left.length = state.start_expression - state.start_line;
					(*other)[depth].right.start = state.end_expression;
					(*other)[depth].right.length = state.end_line - state.end_expression;

					if (state.end_name - state.start_name + 1 > *name_buffer_size) {
						*name_buffer_size = state.end_name - state.start_name + 1;
						*name_buffer = realloc(*name_buffer, sizeof(char) * (*name_buffer_size));
					}
					memcpy(*name_buffer, state.start_name, state.end_name - state.start_name);
					(*name_buffer)[state.end_name - state.start_name] = 0;

					ref_values = PyDict_GetItemString(params, *name_buffer);
					if (ref_values) {
						if (state.strict || PyList_Check(ref_values)) {
							list_size = PyList_Size(ref_values);
							for (j = 0; j < list_size; j++) {
								render_(
									render_result,
									state.start_name,
									state.end_name - state.start_name,
									output_end,
									depth + 1,
									buffer_size,
									other,
									other_size,
									name_buffer,
									name_buffer_size,
									subarrays_length + (*other)[depth].left.length + (*other)[depth].right.length,
									PyList_GetItem(ref_values, j)
								);
							}
						} else {
							render_(
								render_result,
								state.start_name,
								state.end_name - state.start_name,
								output_end,
								depth + 1,
								buffer_size,
								other,
								other_size,
								name_buffer,
								name_buffer_size,
								subarrays_length + (*other)[depth].left.length + (*other)[depth].right.length,
								ref_values
							);
						}
					} else if (!state.optional) {
						render_(
							render_result,
							state.start_name,
							state.end_name - state.start_name,
							output_end,
							depth + 1,
							buffer_size,
							other,
							other_size,
							name_buffer,
							name_buffer_size,
							subarrays_length + (*other)[depth].left.length + (*other)[depth].right.length,
							empty_dict
						);
					}

				}

			}

			if (state.action_type == ACTION_NONE) {
				render__empty(output_end, state.start_line, state.end_line - state.start_line);
			}

			resetState(state);

		}
	break;
/* #line 1508 "compileComprehension.c" */
	}
	}

	}

/* #line 346 "compileComprehension_preprocessed.rl" */


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

	int other_size = 16;
	Other *other = malloc(sizeof(Other) * other_size);

	int name_buffer_size = 128;
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