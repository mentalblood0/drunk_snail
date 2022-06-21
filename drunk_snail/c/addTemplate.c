#include <stdbool.h>



Tree *_templates;


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


void addTemplate_(char *name, char *text) {

	Template *template = malloc(sizeof(Template));

	size_t text_length = strlen(text) + 1;
	template->text = malloc(sizeof(char) * text_length);
	memcpy(template->text, text, text_length);

	template->length = text_length - 1;
	template->buffer_size = template->length;
	template->render_states = NULL;
	template->render_states_current_size = 0;
	template->render_states_allocated_size = 0;

	treeInsert(_templates, name, template);

}


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


static PyObject *addTemplate (
	PyObject *self,
	PyObject *args
) {

	char 
		*name, 
		*template;

	if (!PyArg_ParseTuple(args, "ss", &name, &template))
		return PyLong_FromLong(1);

	addTemplate_(name, template);

	return PyLong_FromLong(0);

}