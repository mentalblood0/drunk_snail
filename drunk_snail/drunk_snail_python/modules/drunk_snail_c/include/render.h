#include <stdlib.h>
#include <sys/types.h>

#include "../modules/memoma/include/memoma.h"

#include "Other.h"
#include "print_macros.h"
#include "params_macros.h"



DRUNK_TYPE empty_dict;


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
	listSet(*other, Other*, depth, &((_line).other), alloc_error);\
	if (alloc_error) {\
		exit_render_();\
	}\
\
}

#define renderParamList(_line) {\
	list_size = DRUNK_LIST_GET_LENGTH(values);\
	for (j = 0; j < list_size; j++) {\
		value = DRUNK_AS_STRING_AND_LENGTH(DRUNK_LIST_GET_ITEM(values, j), &value_size);\
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
			DRUNK_LIST_GET_ITEM(values, j)\
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
				if ((_line).single_expression.flags.strict) {\
					renderParamList(_line);\
				} else if (DRUNK_IS_LIST(values)) {\
					renderParamList(_line);\
				} else {\
					value = DRUNK_AS_STRING_AND_LENGTH(values, &value_size);\
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
			values = DRUNK_PARAMS_GET_ITEM(params, (_line).single_expression.tokens.name.copy);\
\
			if (values) {\
\
				if ((_line).single_expression.flags.strict) {\
					renderRefList(_line);\
				} else if (DRUNK_IS_LIST(values)) {\
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
						values\
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
	DRUNK_TYPE params
);