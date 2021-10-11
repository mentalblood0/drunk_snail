#include "./output_aliases/main.c"



void addTabs(char **s_end, int n) {
	for (; n; n--) {
		**s_end = '\t';
		(*s_end)++;
	}
}


char* compile_(
	char *template_name,
	Tree *templates_tree,
	char **buf,
	__int64 buffer_size,
	int inner_tabs_number,
	char *prefix_start,
	char *prefix_end,
	char *postfix_start,
	char *postfix_end,
	int tabs_number,
	int depth,
	int log
) {

	Template *template = dictionaryLookup(templates_tree, template_name);
	if (template == NULL) {
		if (log)
			printf("Can not compile template \"%s\": not loaded\n", template_name);
		return NULL;
	}
	
	char *s = template->text;

	Keywords *keywords = template->keywords;

	char *result;
	if (buf != NULL) {
		result = *buf;
	}
	else {
		while (!(result = malloc(sizeof(char) * buffer_size)));
	}
	char *result_end = result;

	char *template_name_end = template_name;
	for (; *template_name_end; template_name_end++);

	if (!depth)
		compile__cpy_def();

	int optional = 0;
	int potential_keyword_length = 0;

	clearRefs(template);
	keywords->data[(int)'n']->last_inclusion = s-1;
	keywords->data[(int)'o']->last_inclusion = NULL;
	keywords->data[(int)'c']->last_inclusion = NULL;
	keywords->data[(int)'p']->last_inclusion = NULL;
	keywords->data[(int)'r']->last_inclusion = NULL;
	keywords->data[(int)'?']->last_inclusion = NULL;
	TreeNode *n = &keywords->tree->root;

	char *c = s;
	for (; *c; c++) {
		#include "processCharacter.c"
	}

	if (*(c-1) != '\n') {
		#include "processLine.c"
	}
	
	if (!depth) {
		compile__cpy_return();
		*result_end = 0;
		result = (char*)realloc(result, sizeof(char) * (result_end - result + 1));
	}

	if (buf != NULL)
		*buf = result_end;

	return result;

}


static PyObject *compile (
	PyObject *self,
	PyObject *args
) {

	char *name;
	int log;
	int buffer_size;
	
	if (!PyArg_ParseTuple(args, "sii", &name, &buffer_size, &log)) {
		return PyLong_FromLong(1);
	}

	char *result = compile_(
		name,
		_templates,
		NULL, buffer_size,
		0, NULL, NULL, NULL, NULL, 1, 0, log
	);

	if (result == NULL) {
		return PyLong_FromLong(2);
	}

	return PyUnicode_FromString(result);

}