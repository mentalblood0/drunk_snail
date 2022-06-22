#pragma once

#include <stdbool.h>
#include <sys/types.h>



typedef struct {
	char *start;
	char *end;
} Token;
typedef struct {
	Token line;
	Token expression;
	Token name;
} Tokens;

typedef bool Flag;
typedef struct {
	Flag optional;
	Flag strict;
} Flags;

enum ActionType {
	ACTION_PARAM,
	ACTION_REF,
	ACTION_NONE
};

typedef struct {
	Tokens tokens;
	enum ActionType action;
	Flags flags;
} RenderState;

typedef struct {

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

#define resetToken(token) {\
	token.start = NULL;\
	token.end = NULL;\
}

#define resetFlag(flag) {\
	flag = false;\
}

#define resetRenderState(state) {\
	resetToken(state.tokens.line);\
	resetToken(state.tokens.expression);\
	resetToken(state.tokens.name);\
	state.action = ACTION_NONE;\
	resetFlag(state.flags.optional);\
	resetFlag(state.flags.strict);\
}