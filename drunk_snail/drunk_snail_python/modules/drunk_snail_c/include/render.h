#pragma once


#include <stdlib.h>
#include <sys/types.h>

#include "params_macros.h"
#include "../modules/memoma/include/memoma.h"
#include "../modules/prefix_tree/include/prefix_tree.h"

#include "Other.h"
#include "print_macros.h"
#include "params_macros.h"



typedef struct RenderResult {
	char *message;
	char *result;
	char *result_temp;
} RenderResult;


#define exit_render_() {\
	if (render_result->result) {\
		free(render_result->result);\
		render_result->result = NULL;\
	}\
	if (other) {\
		listFree(*other);\
		free(other);\
	}\
	return;\
}

#define drunk_malloc_one_render_(target, size) {\
	target = malloc(size + (8 - (size % 8)));\
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
	listSet(*other, Other*, depth, &((_line).other), alloc_error);\
\
}

#define renderParamList(_line) {\
	list_size = DRUNK_LIST_GET_LENGTH(values);\
	for (j = 0; j < list_size; j++) {\
		if (DRUNK_AS_STRING_AND_LENGTH(DRUNK_LIST_GET_ITEM(values, j), value, &value_size) == -1) {\
			render_result->message = "Non-bytes value";\
			exit_render_();\
		}\
		render__param(\
			*output_end,\
			(_line).other.left.start, (_line).other.left.length,\
			value, value_size,\
			(_line).other.right.start, (_line).other.right.length\
		);\
	}\
}

#define renderRefList(_line) {\
	list_size = DRUNK_LIST_GET_LENGTH(values);\
	for (j = 0; j < list_size; j++) {\
		render(\
			render_result,\
			(_line).single_expression.tokens.name.start,\
			(_line).single_expression.tokens.name.length,\
			output_end,\
			depth + 1,\
			buffer_size,\
			other,\
			other_left_length + (_line).other.left.length,\
			other_right_length + (_line).other.right.length,\
			DRUNK_LIST_GET_ITEM(values, j),\
			templates_stack\
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
			values = DRUNK_PARAMS_GET_ITEM(params, (_line).single_expression.tokens.name.copy);\
			if (values) {\
				if (DRUNK_IS_LIST(values)) {\
					renderParamList(_line);\
				} else {\
					if (DRUNK_AS_STRING_AND_LENGTH(values, value, &value_size) == -1) {\
						render_result->message = "Non-bytes value";\
						exit_render_();\
					}\
					render__param(\
						*output_end,\
						(_line).other.left.start, (_line).other.left.length,\
						value, value_size,\
						(_line).other.right.start, (_line).other.right.length\
					);\
				}\
			} else if (!(_line).single_expression.flags.optional) {\
				render__param(\
					*output_end,\
					(_line).other.left.start, (_line).other.left.length,\
					value, 0,\
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
			values = DRUNK_PARAMS_GET_ITEM(params, (_line).single_expression.tokens.name.copy);\
\
			if (values) {\
\
				if (DRUNK_IS_LIST(values)) {\
					renderRefList(_line);\
				} else {\
					render(\
						render_result,\
						(_line).single_expression.tokens.name.start,\
						(_line).single_expression.tokens.name.length,\
						output_end,\
						depth + 1,\
						buffer_size,\
						other,\
						other_left_length + (_line).other.left.length,\
						other_right_length + (_line).other.right.length,\
						values,\
						templates_stack\
					);\
					if (!render_result->result) {\
						return;\
					}\
				}\
\
			} else if (!(_line).single_expression.flags.optional) {\
\
				render(\
					render_result,\
					(_line).single_expression.tokens.name.start,\
					(_line).single_expression.tokens.name.length,\
					output_end,\
					depth + 1,\
					buffer_size,\
					other,\
					other_left_length + (_line).other.left.length,\
					other_right_length + (_line).other.right.length,\
					empty_dict,\
					templates_stack\
				);\
				if (!render_result->result) {\
					return;\
				}\
\
			}\
\
			break;\
\
		case ACTION_PARAM_MULTI:\
\
			expression = (_line).param_expressions->start;\
\
			values = DRUNK_PARAMS_GET_ITEM(params, expression->tokens.name.copy);\
			if (values) {\
				if (DRUNK_AS_STRING_AND_LENGTH(values, value, &value_size) == -1) {\
					render_result->message = "Non-bytes value";\
					exit_render_();\
				}\
				render__param_multi_first(\
					*output_end,\
					(_line).other.left.start, (_line).other.left.length,\
					value, value_size,\
					expression->tokens.expression.end, (expression + 1)->tokens.expression.start - expression->tokens.expression.end\
				);\
			}\
\
			++expression;\
\
			for (; expression + 1 - ((_line).param_expressions->start + (_line).param_expressions->length); expression++) {\
\
				values = DRUNK_PARAMS_GET_ITEM(params, expression->tokens.name.copy);\
				if (values) {\
					if (DRUNK_AS_STRING_AND_LENGTH(values, value, &value_size) == -1) {\
						render_result->message = "Non-bytes value";\
						exit_render_();\
					}\
					render__param_multi_between(\
						*output_end,\
						value, value_size,\
						expression->tokens.expression.end, (expression+1)->tokens.expression.start - expression->tokens.expression.end\
					);\
				}\
\
			}\
\
			values = DRUNK_PARAMS_GET_ITEM(params, expression->tokens.name.copy);\
			if (values) {\
				if (DRUNK_AS_STRING_AND_LENGTH(values, value, &value_size) == -1) {\
					render_result->message = "Non-bytes value";\
					exit_render_();\
				}\
				render__param_multi_last(\
					*output_end,\
					value, value_size,\
					expression->tokens.expression.end, (_line).line.end - expression->tokens.expression.end\
				);\
			}\
\
			break;\
\
		default:\
			render__empty(*output_end, (_line).line.start, (_line).line.length);\
			break;\
\
	}\
\
}


void render(
	RenderResult *render_result,
	char *template_name,
	size_t template_name_length,
	char **output_end,
	size_t depth,
	size_t *buffer_size,
	OtherPointerList *other,
	size_t other_left_length,
	size_t other_right_length,
	DRUNK_TYPE params,
	Tree *templates_stack
);