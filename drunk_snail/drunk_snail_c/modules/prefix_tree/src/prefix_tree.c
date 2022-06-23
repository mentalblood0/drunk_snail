#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../memoma/include/memoma.h"
#include "../include/prefix_tree.h"

#define ALPHABET_SIZE 256



Tree* createTree() {
	Tree *tree; drunk_malloc(tree, sizeof(Tree));
	tree->root.value = NULL;
	tree->root.children = calloc(ALPHABET_SIZE, sizeof(TreeNode*));
	return tree;
}


void treeInsert(Tree* tree, char *key, void *value) {

	TreeNode *node = &tree->root;
	char *c = NULL;
	
	for (c = key; *c; c++) {

		TreeNode *parent = node;
		node = node->children[(unsigned char)(*c)];

		if (!node) {
			drunk_malloc(node, sizeof(TreeNode));
			node->value = NULL;
			node->children = calloc(ALPHABET_SIZE, sizeof(TreeNode*));
			parent->children[(unsigned char)(*c)] = node;
		}

	}

	free(node->value);
	node->value = value;

}


void treeRemove(Tree* tree, char *key) {
	
	TreeNode *node = &tree->root;
	char *c = NULL;

	for (c = key; *c; c++) {

		node = node->children[(unsigned char)(*c)];
		if (!node)
			return;

	}

	free(node->value);
	node->value = NULL;

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


void* treeGet(TreeNode *node, char *key) {

	char *c;
	for (c = key; *c; c++) {
		node = node->children[(unsigned char)(*c)];
		if (!node)
			return NULL;
	}

	return node->value;

}


void* treeGetUnterminated(TreeNode *node, char *key, size_t length) {

	size_t i;
	for (i = 0; i < length; i++) {
		node = node->children[(unsigned char)(key[i])];
		if (!node)
			return NULL;
	}

	return node->value;

}


void* dictionaryLookup(Tree *tree, char *key) {
	return treeGet(&tree->root, key);
}


void* dictionaryLookupUnterminated(Tree *tree, char *key, size_t length) {
	return treeGetUnterminated(&tree->root, key, length);
}