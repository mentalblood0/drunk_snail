#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <sys/types.h>
#include "dirent.h"
#include <time.h>
#include "prefix_tree.c"
#include "argparse.c"

char* readFile(char *file_path) {
	char *source = NULL;
	FILE* f = NULL;
	fopen_s(&f, file_path, "r");
	if (f != NULL) {
		if (fseek(f, 0L, SEEK_END) == 0) {
			long bufsize = ftell(f);
			if (bufsize == -1) {
				fclose(f);
				return NULL;
			}
			if (fseek(f, 0L, SEEK_SET) != 0) {
				fclose(f);
				return NULL;
			}

			source = malloc(sizeof(char) * (bufsize + 3));

			size_t newLen = fread(source, sizeof(char), bufsize, f);
			if ( ferror( f ) != 0 ) {
				free(source);
				fclose(f);
				return NULL;
			} else
				source[newLen++] = '\0';
		}
		fclose(f);
	}
	return source;
}

char* getExtension(char* file_name) {
	char *c = file_name;
	for (; *c; c++)
		continue;
	for (; *c != '.'; c--)
		if (c == file_name)
			return NULL;
	return ++c;
}

int strInList(char* str, char* list[]) {
	char **l = list;
	for (; **l != 0; l++)
		if (!strcmp(str, *l))
			return 1;
	return 0;
}

#define cacheTemplates__file_path_length 1024

Tree* cacheTemplates(char* templates_dir_path) {
	Tree *tree = createTree();
	DIR *d = opendir(templates_dir_path);
	if (d != NULL) {
		struct dirent *entry;
		char file_path[cacheTemplates__file_path_length];
		while (1) {
			entry = readdir(d);
			if (!entry)
				break;
			if (entry->d_type == DT_REG) {
				char* extension = getExtension(entry->d_name);
				// if (!strInList(extension, extensions))
				// 	continue;
				snprintf(file_path, cacheTemplates__file_path_length, "%s/%s", templates_dir_path, entry->d_name);
				*(extension - 1) = 0;
				treeInsert(tree, entry->d_name, readFile(file_path));
			}
		}
		closedir(d);
	}
	return tree;
}

typedef struct KeywordData {
	char *last_inclusion;
	int length;
	char last_symbol;
} KeywordData;

typedef struct Keywords {
	Tree *tree;
	KeywordData **data;
} Keywords;

Keywords* createKeywordsData(int number_of_keywords) {
	Keywords *result = malloc(sizeof(Keywords));
	result->tree = createTree();
	result->data = calloc(number_of_keywords, sizeof(KeywordData*));
	return result;
}

void addKeyword(Keywords *keywords, char *keyword, char symbol) {
	char *value_to_insert = malloc(sizeof(char) * 2);
	value_to_insert[0] = symbol;
	value_to_insert[1] = 0;
	treeInsert(keywords->tree, keyword, value_to_insert);

	KeywordData *data = malloc(sizeof(KeywordData));
	data->last_inclusion = NULL;
	char *k = keyword;
	for (; *k; k++);
	data->length = (int)(k - keyword);
	data->last_symbol = *k;
	keywords->data[(int)symbol] = data;
}

#define compile__chunk_size 65536
#define compile__memcpy(src_start, src_end) {memcpy(result_end, src_start, sizeof(char) * (src_end - src_start)); result_end += src_end - src_start;}

char *compile__print_left_part = "result += f'''";
char *compile__print_right_part = "'''\n";
#define compile__cpy_print_left_part() {memcpy(result_end, compile__print_left_part, sizeof(char) * 14); result_end += 14;}
#define compile__cpy_print_right_part() {memcpy(result_end, compile__print_right_part, sizeof(char) * 4); result_end += 4;}
#define compile__cpy_one(c) {*result_end = c; result_end++;}

char *compile__for_strings[11] = {
	"for ",
	" in ([None] if ((not ",
	") or (not '",
	"' in ",
	")) else (",
	"['",
	"'] if type(",
	"['",
	"']) == list else [",
	"['",
	"']])):\n"
};
int compile__for_lengths[11] = {4, 21, 11, 5, 9, 2, 11, 2, 18, 2, 7};
#define compile__for_memcpy(i) compile__memcpy(compile__for_strings[i], compile__for_strings[i] + compile__for_lengths[i]);

#define compile__cpy_for(param_name_start, param_name_end) {\
	compile__for_memcpy(0); compile__memcpy(param_name_start, param_name_end);\
	compile__for_memcpy(1); compile__memcpy(template_name, template_name_end);\
	compile__for_memcpy(2); compile__memcpy(param_name_start, param_name_end);\
	compile__for_memcpy(3); compile__memcpy(template_name, template_name_end);\
	compile__for_memcpy(4); compile__memcpy(template_name, template_name_end);\
	compile__for_memcpy(5); compile__memcpy(param_name_start, param_name_end);\
	compile__for_memcpy(6); compile__memcpy(template_name, template_name_end);\
	compile__for_memcpy(7); compile__memcpy(param_name_start, param_name_end);\
	compile__for_memcpy(8); compile__memcpy(template_name, template_name_end);\
	compile__for_memcpy(9); compile__memcpy(param_name_start, param_name_end);\
	compile__for_memcpy(10);\
}

char *compile__def_strings[2] = {"def render(", "):\n\tresult = ''\n"};
int compile__def_lengths[2] = {11, 16};
#define compile__def_memcpy(i) compile__memcpy(compile__def_strings[i], compile__def_strings[i] + compile__def_lengths[i])

#define compile__cpy_def() {\
	compile__def_memcpy(0); compile__memcpy(template_name, template_name_end);\
	compile__def_memcpy(1);\
}

char *compile__if_strings[4] = {"if ", " and '", "' in ", ":\n"};
int compile__if_lengths[4] = {3, 6, 5, 2};
#define compile__if_memcpy(i) compile__memcpy(compile__if_strings[i], compile__if_strings[i] + compile__if_lengths[i])

#define compile__cpy_if(param_name_start, param_name_end) {\
	compile__if_memcpy(0); compile__memcpy(template_name, template_name_end);\
	compile__if_memcpy(1); compile__memcpy(param_name_start, param_name_end);\
	compile__if_memcpy(2); compile__memcpy(template_name, template_name_end);\
	compile__if_memcpy(3);\
}

char *compile__return = "\treturn result\n";
int compile__return_length = 15;

void addTabs(char **s_end, int n) {
	for (; n; n--) {
		**s_end = '\t';
		(*s_end)++;
	}
}

char* compile(
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
	keywords->data[(int)'n']->last_inclusion = s;
	TreeNode *n = &keywords->tree->root;
	for (; *c; c++) {
		if (n->children[(int)*c])
			n = n->children[(int)*c];
		else {
			if (n->value) {
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
	return result;
}

#define compileTemplates__file_path_length 128

void compileTemplates_(
	char *templates_dir_path, 
	char *compiled_dir_path, 
	Keywords *keywords, 
	Tree *templates_tree,
	int log
) {
	DIR *d = opendir(templates_dir_path);
	if (d != NULL) {
		struct dirent *entry;
		char file_path[compileTemplates__file_path_length];
		char compiled_path[compileTemplates__file_path_length];
		while (1) {
			entry = readdir(d);
			if (!entry)
				break;
			if (entry->d_type == DT_REG) {
				char* extension = getExtension(entry->d_name);
				snprintf(file_path, compileTemplates__file_path_length, "%s/%s", templates_dir_path, entry->d_name);
				*(extension - 1) = 0;
				char *compiled = compile(entry->d_name, keywords, templates_tree, 0, NULL, NULL, NULL, NULL, 1, 0, log);
				size_t compiled_length = strlen(compiled);
				snprintf(compiled_path, compileTemplates__file_path_length, "%s/%s.py", compiled_dir_path, entry->d_name);
				FILE *f = fopen(compiled_path, "w");
				if (f != NULL) {
					if (log) {
						printf("%s -> %s (%I64d chars)\n", file_path, compiled_path, compiled_length);
					}
					fwrite(compiled, sizeof(char), compiled_length, f);
				}
				fclose(f);
			}
		}
		closedir(d);
	}
}

#include <Python.h>

static PyObject *compileTemplates (
	PyObject *self,
	PyObject *args
) {

	char 
		*input_dir, 
		*output_dir,
		*open_tag,
		*close_tag,
		*param_operator,
		*ref_operator,
		*optional_operator;
	int 
		log;

	if (!PyArg_ParseTuple(args, "sssssssi",
		&input_dir,
		&output_dir,
		&open_tag,
		&close_tag,
		&param_operator,
		&ref_operator,
		&optional_operator,
		&log
	)) {
		return PyLong_FromLong(1);
	}

	Tree *templates_tree = cacheTemplates(input_dir);
	
	Keywords *keywords = createKeywordsData(128);
	addKeyword(keywords, "\n", 'n');
	addKeyword(keywords, open_tag, 'o');
	addKeyword(keywords, close_tag, 'c');
	addKeyword(keywords, param_operator, 'p');
	addKeyword(keywords, ref_operator, 'r');
	addKeyword(keywords, optional_operator, '?');

	compileTemplates_(
		input_dir,
		output_dir,
		keywords,
		templates_tree,
		log
	);

	return PyLong_FromLong(0);

}


static PyMethodDef methods[] = {
	{"compileTemplates", compileTemplates, METH_VARARGS, "Interface for drunk_snail C library"},
	{NULL, NULL, 0, NULL}
};

static struct PyModuleDef compileTemplatesModule = {
	PyModuleDef_HEAD_INIT,
	"compileTemplates",
	"Interface for drunk_snail C library",
	-1,
	methods
};

PyMODINIT_FUNC PyInit_compileTemplates(void) {
	return PyModule_Create(&compileTemplatesModule);
}