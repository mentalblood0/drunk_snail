#pragma once

#include <stdbool.h>
#include <sys/types.h>



enum ActionType {
	ACTION_PARAM,
	ACTION_REF,
	ACTION_NONE
};

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

typedef struct Template {

	char *text;
	size_t length;
	size_t buffer_size;

	size_t render_states_current_size;
	size_t render_states_allocated_size;
	RenderState *render_states;

} Template;


#define addRenderState(template, state) {\
\
	template->render_states_current_size += 1;\
\
	if (template->render_states_current_size > template->render_states_allocated_size) {\
		if (template->render_states == NULL) {\
			template->render_states_allocated_size = 16;\
			template->render_states = malloc(sizeof(RenderState) * template->render_states_allocated_size);\
		} else {\
			template->render_states_allocated_size *= 2;\
			template->render_states = realloc(template->render_states, sizeof(RenderState) * template->render_states_allocated_size);\
		}\
	}\
\
	template->render_states[template->render_states_current_size-1] = state;\
\
}

#define resetRenderState(state) {\
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