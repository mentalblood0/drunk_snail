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
	FILE* fp = NULL;
	fopen_s(&fp, file_path, "r");
	if (fp != NULL) {
	    /* Go to the end of the file. */
	    if (fseek(fp, 0L, SEEK_END) == 0) {
	        /* Get the size of the file. */
	        long bufsize = ftell(fp);
	        if (bufsize == -1) {
	        	return NULL;
	        }

	        /* Allocate our buffer to that size. */
	        source = malloc(sizeof(char) * (bufsize + 1));

	        /* Go back to the start of the file. */
	        if (fseek(fp, 0L, SEEK_SET) != 0) {
	        	return NULL;
	        }

	        /* Read the entire file into memory. */
	        size_t newLen = fread(source, sizeof(char), bufsize, fp);
	        if ( ferror( fp ) != 0 ) {
	            return NULL;
	        } else {
	            source[newLen++] = '\0'; /* Just to be safe. */
	        }
	    }
	    fclose(fp);
	}
	return source;
}

Tree* cacheTemplates(char* templates_dir_path) {
	Tree *tree = createTree();
	DIR *d = opendir(templates_dir_path);
	if (d != NULL) {
		struct dirent *entry;
		char file_path[128];
		while (1) {
			entry = readdir(d);
			if (entry) {
				char* extension = getExtension(entry->d_name);
				if (!strcmp(extension, "xml") || !strcmp(extension, "txt")) {
					snprintf(file_path, 128, "%s\\%s", templates_dir_path, entry->d_name);
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

#define compile__chunk_size 10000
#define compile__memcpy(src_start, src_end) {memcpy(result_end, src_start, src_end - src_start); result_end += src_end - src_start;}

char *compile__print_left_part = "print(f'''";
char *compile__print_right_part = "''')\n";
#define compile__cpy_print_left_part() {memcpy(result_end, compile__print_left_part, 10); result_end += 10;}
#define compile__cpy_print_right_part() {memcpy(result_end, compile__print_right_part, 5); result_end += 5;}
#define compile__cpy_one(c) {*result_end = c; result_end++;}

int printFromTo(char *s, char *from_p, char *to_p, char *comment) {
	if (from_p > to_p) return 0;
	char temp = *to_p;
	*to_p = 0;
	printf("\n____%s ([%I64d:%I64d]): \"%s\"\n", comment, from_p - s, to_p - s, from_p);
	*to_p = temp;
	return 1;
}

int compile_calls = 0;

char* compile(char *s, Keywords *keywords, Tree *templates_tree) {
	compile_calls += 1;
	char *result;
	while (!(result = malloc(sizeof(char) * compile__chunk_size)));
	char *result_end = result;
	char *c = s;
	int tag_on_this_line = 0;
	keywords->data[(int)'n']->last_inclusion = s;
	TreeNode *n = &keywords->tree->root;
	for (; *c; c++) {
		if (n->children[(int)*c])
			n = n->children[(int)*c];
		else {
			if (n->value) {
				if (n->value[0] == 'o')
					tag_on_this_line = 1;
				if (n->value[0] == 'n') {
					if (tag_on_this_line) {
						char *open_last = keywords->data[(int)'o']->last_inclusion;
						// BEFORE
						char *prev_line_break = keywords->data[(int)'n']->last_inclusion;
						char *line_before_open_tag_start = prev_line_break + 1;
						char *line_before_open_tag_end = open_last;
						if (line_before_open_tag_start <= line_before_open_tag_end) {
							// AFTER
							KeywordData *close_data = keywords->data[(int)'c'];
							char *close_last = close_data->last_inclusion;
							char *line_after_close_tag_start = close_last + close_data->length;
							char *line_after_close_tag_end = c - 1;
							// PARAM
							KeywordData *param_data = keywords->data[(int)'p'];
							char *param_last = param_data->last_inclusion;
							if (param_last) {
								char *param_name_start = param_last + param_data->length;
								char *param_name_end = param_name_start;
								for (; *param_name_end != ' '; param_name_end++);

								compile__cpy_print_left_part();
								compile__memcpy(line_before_open_tag_start, line_before_open_tag_end);
								compile__cpy_one('{');
								compile__memcpy(param_name_start, param_name_end);
								compile__cpy_one('}');
								compile__memcpy(line_after_close_tag_start, line_after_close_tag_end);
								compile__cpy_print_right_part();
							}
							// REF
							KeywordData *ref_data = keywords->data[(int)'r'];
							char *ref_last = ref_data->last_inclusion;
							if (ref_last) {
								char *ref_name_start = ref_last + ref_data->length;
								char *ref_name_end = ref_name_start;
								for (; *ref_name_end != ' '; ref_name_end++);

								char temp = *ref_name_end;
								*ref_name_end = 0;
								char *subtemplate_text = compile(dictionaryLookup(templates_tree, ref_name_start), keywords, templates_tree);
								*ref_name_end = temp;
								compile__memcpy(subtemplate_text, subtemplate_text + strlen(subtemplate_text));
								compile__cpy_one('\n');
							}
						}
						tag_on_this_line = 0;
					} else {
						char *prev_line_break = keywords->data[(int)'n']->last_inclusion;
						char *line_start = prev_line_break + 1;
						char *line_end = c - 1;
						compile__cpy_print_left_part();
						compile__memcpy(line_start, line_end);
						compile__cpy_print_right_part();
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
	*result_end = 0;
	result = (char*)realloc(result, sizeof(char) * (strlen(result) + 1));
	return result;
}

int main (void) {
	Tree *templates_tree = cacheTemplates("C:\\Users\\Necheporenko_s_iu\\repositories\\two_servers\\template_engine\\templates");
	// printf("%s\n", dictionaryLookup(templates_tree, "Notification"));

	Keywords *keywords = createKeywordsData(5);
	addKeyword(keywords, "\n", 'n');
	addKeyword(keywords, "<!--", 'o');
	addKeyword(keywords, "-->", 'c');
	addKeyword(keywords, "(param)", 'p');
	addKeyword(keywords, "(ref)", 'r');

	// int i = 0;
	// clock_t t = clock();
	// for (; i < 1000; i++)
	// 	free(compile(dictionaryLookup(templates_tree, "Notification"), keywords, templates_tree));
	// t = clock() - t;
	// printf("%f\n", ((double)t) / CLOCKS_PER_SEC);

	printf("result:\n%s\n", compile(dictionaryLookup(templates_tree, "Notification"), keywords, templates_tree));
	printf("compile_calls %d\n", compile_calls);
	printf("end\n");

	return 0;
}