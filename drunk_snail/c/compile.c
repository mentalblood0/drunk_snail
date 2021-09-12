#include "output_aliases.c"



void addTabs(char **s_end, int n) {
	for (; n; n--) {
		**s_end = '\t';
		(*s_end)++;
	}
}


char* compile_(
	char *template_name,
	Keywords *keywords,
	Tree *templates_tree,
	int inner_tabs_number,
	char *prefix_start,
	char *prefix_end,
	char *postfix_start,
	char *postfix_end,
	int tabs_number,
	int depth,
	int log
) {

	printf("compiling template\"%s\"\n", template_name);
	
	char *s = dictionaryLookup(templates_tree, template_name);
	if (!s) {
		if (log)
			printf("Can not compile template \"%s\": no corresponding file found\n", template_name);
		return NULL;
	}

	char *result;
	while (!(result = malloc(sizeof(char) * compile__chunk_size)));
	char *result_end = result;

	char *c = s;

	char *template_name_end = template_name;
	for (; *template_name_end; template_name_end++);

	if (!depth)
		compile__cpy_def();

	int tag_on_this_line = 0;
	int optional = 0;
	int child_exists = 0;

	keywords->data[(int)'n']->last_inclusion = s;
	TreeNode *n = &keywords->tree->root;

	for (; *c; c++) {

		if (n) {
			if (n->children[(int)*c]) {
				n = n->children[(int)*c];
				child_exists = 1;
			}
			else {
				child_exists = 0;
			}
		}

		if (!child_exists) {

			if (n)
				if (n->value) {

					printf("%s", n->value);

					if ((n->value[0] == 'r') || (n->value[0] == 'p'))
						tag_on_this_line = 1;

					if (n->value[0] == '?')
						optional = 1;

					if (n->value[0] == 'n') {
						#include "processLine.c"
						keywords->data[(int)'p']->last_inclusion = NULL;
						keywords->data[(int)'r']->last_inclusion = NULL;
						++c;
					}

					KeywordData *current_keyword_data = keywords->data[(int)n->value[0]];
					current_keyword_data->last_inclusion = c - current_keyword_data->length;
					--c;

				}

			n = &keywords->tree->root;

		}

	}

	#include "processLine.c"
	
    if (!depth)
		compile__memcpy(compile__return, compile__return + compile__return_length);
	
    *result_end = 0;
	result = (char*)realloc(result, sizeof(char) * (result_end - result + 1));
	
	printf("\n");
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
        _keywords, 
        _templates,
        0, NULL, NULL, NULL, NULL, 1, 0, log
    );

	return PyUnicode_FromString(result);

}