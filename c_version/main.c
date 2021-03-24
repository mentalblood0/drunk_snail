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

#define compile_chunk_size 10000
#define compile_buf_size 10000

char* compile(char *s, Tree *keywords_tree) {
	char *result = malloc(sizeof(char) * compile_chunk_size);
	char *c = s;
	char **last_keywords_indexes = calloc(128, sizeof(char*));
	last_keywords_indexes[(int)'l'] = s;
	TreeNode *n = &keywords_tree->root;
	for (; *c; c++) {
		if (n->children[(int)*c])
			n = n->children[(int)*c];
		else {
			if (n->value) {
				last_keywords_indexes[(int)n->value[0]] = c;
				if (n->value[0] == 'n') {
					if (last_keywords_indexes[(int)'o']) {
						*(last_keywords_indexes[(int)'o'] - 1) = 0;
						printf("|%s|\n", last_keywords_indexes[(int)'l']);
						*(last_keywords_indexes[(int)'o'] - 1) = '-';
					}
				}
			}
			n = &keywords_tree->root;
		}

	}
	return result;
}

int main (void) {
	Tree *templates_tree = cacheTemplates("../templates");
	printf("%s\n", dictionaryLookup(templates_tree, "Notification"));

	Tree *keywords_tree = createTree();
	treeInsert(keywords_tree, "\n", "n");
	treeInsert(keywords_tree, "<!--", "o");
	treeInsert(keywords_tree, "-->", "c");
	treeInsert(keywords_tree, "(param)", "p");
	treeInsert(keywords_tree, "(ref)", "r");

	printf("\n");
	compile(dictionaryLookup(templates_tree, "Notification"), keywords_tree);

	return 0;
}