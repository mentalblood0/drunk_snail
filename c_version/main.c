#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include "prefix_tree.c"

char* getExtension(char* file_name) {
	char* c = file_name;
	for (; *c; c++)
		continue;
	for (; *c != '.'; c--)
		continue;
	return ++c;
}

void* _realloc(void *p, size_t size) {
	void *result;
	while (!(result = malloc(size)));
	free(p);
	return result;
}

#define readFile_chunk_size 128

char* readFile(char *file_path) {
	char *source = NULL;
	FILE* f = NULL;
	fopen_s(&f, file_path, "r");
	if (f != NULL) {
		/* Go to the end of the file. */
		if (fseek(f, 0L, SEEK_END) == 0) {
			/* Get the size of the file. */
			long bufsize = ftell(f);
			if (bufsize == -1) {
				fclose(f);
				return NULL;
			}

			/* Go back to the start of the file. */
			if (fseek(f, 0L, SEEK_SET) != 0) {
				fclose(f);
				return NULL;
			}

			/* Allocate our buffer to that size. */
			source = malloc(sizeof(char) * (bufsize + 3));

			/* Read the entire file into memory. */
			size_t newLen = fread(source, sizeof(char), bufsize, f);
			if ( ferror( f ) != 0 ) {
				free(source);
				fclose(f);
				return NULL;
			} else {
				source[newLen++] = '\0'; /* Just to be safe. */
			}
		}
		fclose(f);
	}
	return source;
}

#define cacheTemplates__file_path_length 128

Tree* cacheTemplates(char* templates_dir_path) {
	Tree *tree = createTree();
	DIR *d = opendir(templates_dir_path);
	if (d != NULL) {
		struct dirent *entry;
		char file_path[cacheTemplates__file_path_length];
		while (1) {
			entry = readdir(d);
			if (entry) {
				char* extension = getExtension(entry->d_name);
				if (!strcmp(extension, "xml") || !strcmp(extension, "txt")) {
					snprintf(file_path, cacheTemplates__file_path_length, "%s\\%s", templates_dir_path, entry->d_name);
					*(extension - 1) = 0;
					treeInsert(tree, entry->d_name, readFile(file_path));
				}
			}
			else
				break;
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
	data->length = k - keyword;
	data->last_symbol = *k;
	keywords->data[(int)symbol] = data;
}

#define compile__chunk_size 40000
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

// char temp = *param_name_end;
// 	*param_name_end = '\0';
// 	result_end += sprintf(result_end, "for %s in ([None] if ((not %s) or (not '%s' in %s)) else (%s['%s'] if type(%s['%s']) == list else [%s['%s']])):", param_name_start, template_name, param_name_start, template_name, template_name, param_name_start, template_name, param_name_start, template_name, param_name_start);
// 	*param_name_end = temp;

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

char *compile__if_strings[3] = {"if '", "' in ", ":\n"};
int compile__if_lengths[3] = {4, 5, 2};
#define compile__if_memcpy(i) compile__memcpy(compile__if_strings[i], compile__if_strings[i] + compile__if_lengths[i])

#define compile__cpy_if(param_name_start, param_name_end) {\
	compile__if_memcpy(0); compile__memcpy(param_name_start, param_name_end);\
	compile__if_memcpy(1); compile__memcpy(template_name, template_name_end);\
	compile__if_memcpy(2);\
}

char *compile__return = "\treturn result\n";
int compile__return_length = 15;

int printFromTo(char *s, char *from_p, char *to_p, char *comment, char *template_name) {
	if (from_p > to_p) return 0;
	char temp = *to_p;
	*to_p = 0;
	printf("____%s____%s ([%I64d:%I64d]): \"%s\"\n", template_name, comment, from_p - s, to_p - s, from_p);
	*to_p = temp;
	return 1;
}

void addTabs(char **s_end, int n) {
	for (; n; n--) {
		**s_end = '\t';
		(*s_end)++;
	}
}

int compile_calls = 0;

char* compile(char *template_name, Keywords *keywords, Tree *templates_tree, int inner_tabs_number, char *prefix_start, char *prefix_end, char *postfix_start, char *postfix_end, int tabs_number, int depth) {
	char *s = dictionaryLookup(templates_tree, template_name);
	compile_calls += 1;
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
					if (tag_on_this_line) {
						#include "processLineWithTag.c"
					} else {
						#include "processLineWithoutTag.c"
					}
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
	if (tag_on_this_line) {
		#include "processLineWithTag.c"
	} else {
		#include "processLineWithoutTag.c"
	}
	if (!depth)
		compile__memcpy(compile__return, compile__return + compile__return_length);
	*result_end = 0;
	result = (char*)realloc(result, sizeof(char) * (result_end - result + 1));
	return result;
}

#define compileTemplates__file_path_length 128

void compileTemplates(char *templates_dir_path, char *compiled_dir_path, Keywords *keywords, Tree *templates_tree) {
	DIR *d = opendir(templates_dir_path);
	if (d != NULL) {
		struct dirent *entry;
		char file_path[compileTemplates__file_path_length];
		char compiled_path[compileTemplates__file_path_length];
		while (1) {
			entry = readdir(d);
			if (entry) {
				char* extension = getExtension(entry->d_name);
				if (!strcmp(extension, "xml") || !strcmp(extension, "txt")) {
					snprintf(file_path, compileTemplates__file_path_length, "%s\\%s", templates_dir_path, entry->d_name);
					*(extension - 1) = 0;
					char *compiled = compile(entry->d_name, keywords, templates_tree, 0, NULL, NULL, NULL, NULL, 1, 0);
					size_t compiled_length = strlen(compiled);
					snprintf(compiled_path, compileTemplates__file_path_length, "%s\\%s.py", compiled_dir_path, entry->d_name);
					FILE *f = fopen(compiled_path, "w");
					if (f != NULL) {
						printf("%s -> %s (%I64d chars)\n", file_path, compiled_path, compiled_length);
						fwrite(compiled, sizeof(char), compiled_length, f);
					}
					fclose(f);
				}
			}
			else
				break;
		}
		closedir(d);
	}
}

int main (void) {
	Tree *templates_tree = cacheTemplates("C:\\Users\\Necheporenko_s_iu\\repositories\\two_servers\\templates");
	// printf("%s\n", dictionaryLookup(templates_tree, "Notification"));

	Keywords *keywords = createKeywordsData(128);
	addKeyword(keywords, "\n", 'n');
	addKeyword(keywords, "<!--", 'o');
	addKeyword(keywords, "-->", 'c');
	addKeyword(keywords, "(param)", 'p');
	addKeyword(keywords, "(ref)", 'r');
	addKeyword(keywords, "(optional)", '?');

	compileTemplates(
		"C:\\Users\\Necheporenko_s_iu\\repositories\\two_servers\\templates",
		"C:\\Users\\Necheporenko_s_iu\\repositories\\two_servers\\compiled_templates",
		keywords,
		templates_tree
	);

	// int i = 0;
	// clock_t t = clock();
	// for (; i < 1000; i++)
	// 	free(compile("Notification", keywords, templates_tree, 0, NULL, NULL, NULL, NULL, 1, 0));
	// t = clock() - t;
	// printf("%f\n", ((double)t) / CLOCKS_PER_SEC);

	// char *compiled = compile("Notification", keywords, templates_tree, 0, NULL, NULL, NULL, NULL, 1, 0);
	// int compiled_length = strlen(compiled);
	// FILE *f = fopen("compiled.py", "w");
	// if (f != NULL) {
	// 	printf("writing %d chars\n", compiled_length);
	// 	fwrite(compiled, sizeof(char), compiled_length, f);
	// }

	return 0;
}