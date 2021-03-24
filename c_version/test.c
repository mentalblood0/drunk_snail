#include "prefix_tree.c"
#include <sysinfoapi.h>

void insert(Tree *tree, char *word) {
	tree_insert(tree, word, word);
	printf("inserted %s; found %s\n", word, dictionary_lookup(tree, word));
}

void printMemoryStatus() {
	MEMORYSTATUSEX mse;
	mse.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&mse);
	printf("%I64u\n", (unsigned long long)mse.ullAvailPhys);
}

int main(void) {
	printMemoryStatus();
	Tree *tree = createTree();
	insert(tree, "lalala");
	insert(tree, "fsdafsadfs");
	printMemoryStatus();
	clearTree(tree);
	printMemoryStatus();
	char *word = "lalala";
	printf("inserted %s; found %s\n", word, dictionary_lookup(tree, word));
	printMemoryStatus();
	return 0;
}