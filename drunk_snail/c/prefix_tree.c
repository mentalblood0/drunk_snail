#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 128



typedef struct TreeNode {
	void *value;
	struct TreeNode **children;
} TreeNode;


typedef struct Tree {
	TreeNode root;
} Tree;


Tree* createTree() {
	Tree *tree = malloc(sizeof(Tree));
	tree->root.value = NULL;
	tree->root.children = calloc(ALPHABET_SIZE, sizeof(TreeNode*));
	return tree;
}


int treeInsert(Tree* tree, char *word, char *description) {
	
	TreeNode *node = &tree->root;
	char *c = NULL;
	
	for (c = word; *c; c++) {

		if ((int)(*c) == -1)
			return 1;

		TreeNode *parent = node;
		node = node->children[(int)(*c)];

		if (!node) {
			node = malloc(sizeof(TreeNode));
			node->value = NULL;
			node->children = calloc(ALPHABET_SIZE, sizeof(TreeNode*));
			parent->children[(int)(*c)] = node;
		}
	
	}

	if (node->value) {
		free(node->value);
	}

	int description_len = (int)strlen(description);
	node->value = malloc(sizeof(char) * (description_len + 1));
	strncpy_s(node->value, sizeof(char) * (description_len + 1), description, description_len);
	
	return 0;

}


int treeRemove(Tree* tree, char *word) {
	
	TreeNode *node = &tree->root;
	char *c = NULL;
	
	for (c = word; *c; c++) {
	
		if ((int)(*c) == -1)
			return 1;

		TreeNode *parent = node;
		node = node->children[(int)(*c)];
		if (!node)
			return 0;

	}

	if (node->value) {
		free(node->value);
		node->value = NULL;
	}

	return 0;

}


void freeNodes(TreeNode *node) {

	if (node == NULL)
		return;
	
	free(node->value);
	
	TreeNode **children = node->children;

	int i;
	for (i = 0; i < ALPHABET_SIZE; i++)
		if (children[i] != NULL)
			freeNodes(children[i]);
	
	free(children);
	free(node);

}


void clearTree(Tree *tree) {
	
	int i;
	
	for (i = 0; i < ALPHABET_SIZE; i++)
		if (tree->root.children[i] != NULL) {
			freeNodes(tree->root.children[i]);
			tree->root.children[i] = NULL;
		}

}


void* treeGet(TreeNode *node, char *word) {

	char *c = NULL;
	
	for (c = word; *c; c++) {

		if ((int)(*c) == -1)
			return NULL;
		
		node = node->children[(int)(*c)];
		if (!node)
			return NULL;
	
	}

	return node->value;

}


void* dictionaryLookup(Tree *tree, char *word) {
	return treeGet(&tree->root, word);
}