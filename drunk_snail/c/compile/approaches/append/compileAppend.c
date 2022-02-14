#include "./output_aliases/main.c"



void compileAppend_(
	CompilationResult *compilation_result,
	char *template_name,
	Tree *templates_tree,
	char **buf,
	int buffer_size,
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
		compilation_result->code = 1;
		compilation_result->message = malloc(sizeof(char) * 256);
		snprintf(
			compilation_result->message, 
			256, 
			"Can not compile template \"%s\": not loaded\n", 
			template_name
		);
		return;
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
		compileAppend__cpy_def();

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
		#include "processCharacterAppend.c"
	}

	if (*(c-1) != '\n') {
		#include "processLineAppend.c"
	}
	
	if (!depth) {
		compileAppend__cpy_return();
		*result_end = 0;
		result = (char*)realloc(result, sizeof(char) * (result_end - result + 1));
	}

	if (buf != NULL)
		*buf = result_end;

	compilation_result->code = 0;
	if (!depth)
		compilation_result->result = result;
	return;

}


static PyObject *compileAppend (
	PyObject *self,
	PyObject *args
) {

	char *name;
	int log;
	int buffer_size;
	
	if (!PyArg_ParseTuple(args, "sii", &name, &buffer_size, &log)) {
		return PyLong_FromLong(-1);
	}

	CompilationResult *compilation_result = malloc(sizeof(CompilationResult) * 1);
	compilation_result->code = 0;
	compilation_result->message = NULL;
	compilation_result->result = NULL;
	compileAppend_(
		compilation_result,
		name,
		_templates,
		NULL, buffer_size,
		0, NULL, NULL, NULL, NULL, 1, 0, log
	);

	PyObject *t = PyTuple_New(3);
	PyTuple_SetItem(t, 0, PyLong_FromLong(compilation_result->code));
	if (compilation_result->message)
		PyTuple_SetItem(t, 1, PyUnicode_FromString(compilation_result->message));
	else
		PyTuple_SetItem(t, 1, PyUnicode_FromString(""));
	if (compilation_result->result)
		PyTuple_SetItem(t, 2, PyUnicode_FromString(compilation_result->result));
	else
		PyTuple_SetItem(t, 2, PyUnicode_FromString(""));
	
	free(compilation_result);

	return t;

}