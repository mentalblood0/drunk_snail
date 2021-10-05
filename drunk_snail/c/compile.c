#include "output_aliases.c"



void addTabs(char **s_end, int n) {
	for (; n; n--) {
		**s_end = '\t';
		(*s_end)++;
	}
}


#define compile__initial_chunk_size 65536

char* compile_(
	char *template_name,
	Tree *templates_tree,
	char **buf,
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
	
	char *s = template->text;
	if (!s) {
		if (log)
			printf("Can not compile template \"%s\": no corresponding file found\n", template_name);
		return NULL;
	}
	fprintf(stderr, "compile_:\n%s\n", s);

	Keywords *keywords = template->keywords;

	char *result;
	if (buf != NULL) {
		result = *buf;
	}
	else {
		while (!(result = malloc(sizeof(char) * compile__initial_chunk_size)));
	}
	char *result_end = result;

	char *template_name_end = template_name;
	for (; *template_name_end; template_name_end++);

	if (!depth)
		compile__cpy_def();

	int optional = 0;
	int potential_keyword_length = 0;

	keywords->data[(int)'n']->last_inclusion = s-1;
	TreeNode *n = &keywords->tree->root;

	char *c = s;
	for (; *c; c++) {
		#include "processCharacter.c"
	}

	if (*(c-1) != '\n') {
		#include "processLine.c"
	}
	
	if (!depth) {
		compile__memcpy(compile__return, compile__return + compile__return_length);
		*result_end = 0;
		result = (char*)realloc(result, sizeof(char) * (result_end - result + 1));
	}

	if (buf != NULL)
		*buf = result_end;
	
	fprintf(stderr, "compile_ result:\n%s\n", result);

	return result;

}


static PyObject *compile (
	PyObject *self,
	PyObject *args
) {

	char *name;
	int log;
	
	if (!PyArg_ParseTuple(args, "si", &name, &log)) {
		return PyLong_FromLong(1);
	}

	char *result = compile_(
		name,
		_templates,
		NULL,
		0, NULL, NULL, NULL, NULL, 1, 0, log
	);

	return PyUnicode_FromString(result);

}