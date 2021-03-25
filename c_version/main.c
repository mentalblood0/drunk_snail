#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include "prefix_tree.c"

char* getExtension(char* file_name) {
	char* c = file_name;
	for (; *c; c++)
		continue;
	for (; *c != '.'; c--)
		continue;
	return ++c;
}

#define readFile_chunk_size 128

char* readFile(char *file_path) {
	FILE *f = fopen(file_path, "r");
	if (f == NULL)
		return NULL;
	
	char *result = NULL;
	unsigned long long chars_read = 0;
	unsigned long long current_chars_read;
	size_t chunk_size = sizeof(char) * readFile_chunk_size;
	size_t current_size = 0;
	while (1) {
		current_size += chunk_size;
		result = (char*)realloc(result, current_size);
		current_chars_read = fread(result + chars_read, sizeof(char), readFile_chunk_size, f);
		chars_read += current_chars_read; 
		result[chars_read] = 0;
		if (current_chars_read == 0)
			break;
	}
	
	fclose(f);
	return result;
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
					snprintf(file_path, 128, "%s/%s", templates_dir_path, entry->d_name);
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

#define compile_chunk_size 10000
#define compile_buf_size 10000

char* compile(char *s, Keywords *keywords) {
	char *result = malloc(sizeof(char) * compile_chunk_size);
	char *c = s;
	keywords->data[(int)'n']->last_inclusion = s;
	TreeNode *n = &keywords->tree->root;
	for (; *c; c++) {
		printf("%c", *c);
		if (n->children[(int)*c])
			n = n->children[(int)*c];
		else {
			if (n->value) {
				if (n->value[0] == 'n') {
					char *open_last = keywords->data[(int)'o']->last_inclusion;
					if (open_last) {
						char *prev_line_break = keywords->data[(int)'n']->last_inclusion;
						// char *line_break = c - 1;
						char *line_before_open_tag_start = prev_line_break + 1;
						char *line_before_open_tag_end = open_last;
						if (line_before_open_tag_start <= line_before_open_tag_end) {
							char temp = *line_before_open_tag_end;
							*line_before_open_tag_end = 0;
							printf("\n\tline before open tag ([%I64d:%I64d]): '%s'\n", line_before_open_tag_start - s, line_before_open_tag_end - s, line_before_open_tag_start);
							*line_before_open_tag_end = temp;
						}
					} else printf("\n\tno keywords->data[(int)'o']->last_inclusion\n");
				}
				KeywordData *current_keyword_data = keywords->data[(int)n->value[0]];
				current_keyword_data->last_inclusion = c - current_keyword_data->length;
			}
			n = &keywords->tree->root;
		}

	}
	return result;
}

int main (void) {
	Tree *templates_tree = cacheTemplates("../templates");
	// printf("%s\n", dictionaryLookup(templates_tree, "Notification"));

	Keywords *keywords = createKeywordsData(5);
	addKeyword(keywords, "\n", 'n');
	addKeyword(keywords, "<!--", 'o');
	addKeyword(keywords, "-->", 'c');
	addKeyword(keywords, "(param)", 'p');
	addKeyword(keywords, "(ref)", 'r');

	printf("\n");
	compile(dictionaryLookup(templates_tree, "Notification"), keywords);

	return 0;
}