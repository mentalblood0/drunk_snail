#include <string.h>

#include "../modules/memoma/include/memoma.h"



#define render__empty(target, LINE, LINE_length) {\
	required_buffer_size = ((target) - render_result->result) + (LINE_length+1) + other_left_length + other_right_length;\
	if (required_buffer_size >= *buffer_size) {\
		(*buffer_size) = 2 * required_buffer_size;\
		drunk_realloc_with_shifted(render_result->result, sizeof(char) * (*buffer_size), render_result->result_temp, target, alloc_error);\
		if (alloc_error) {\
			exit_render_();\
		}\
	}\
	for (i = 0; i < depth; i++) {\
		drunk_memcpy((target), other_start[i].left.start, other_start[i].left.length);\
	}\
	drunk_memcpy((target), LINE, LINE_length);\
	if (other_right_length) {\
		for (i = depth; i > 0; i--) {\
			drunk_memcpy((target), other_start[i-1].right.start, other_start[i-1].right.length);\
		}\
	}\
	*target = '\n'; ++target;\
};

#define render__param(target, OTHER_LEFT, OTHER_LEFT_length, ARG, ARG_length, OTHER_RIGHT, OTHER_RIGHT_length) {\
	required_buffer_size = ((target) - render_result->result) + (OTHER_LEFT_length+ARG_length+OTHER_RIGHT_length+1) + other_left_length + other_right_length;\
	if (required_buffer_size >= *buffer_size) {\
		(*buffer_size) = 2 * required_buffer_size;\
		drunk_realloc_with_shifted(render_result->result, sizeof(char) * (*buffer_size), render_result->result_temp, target, alloc_error);\
		if (alloc_error) {\
			exit_render_();\
		}\
	}\
	for (i = 0; i < depth; i++) {\
		drunk_memcpy((target), other_start[i].left.start, other_start[i].left.length);\
	}\
	drunk_memcpy((target), OTHER_LEFT, OTHER_LEFT_length);\
	drunk_memcpy((target), ARG, ARG_length);\
	drunk_memcpy((target), OTHER_RIGHT, OTHER_RIGHT_length);\
	if (other_right_length) {\
		for (i = depth; i > 0; i--) {\
			drunk_memcpy((target), other_start[i-1].right.start, other_start[i-1].right.length);\
		}\
	}\
	*target = '\n'; ++target;\
};