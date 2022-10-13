#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../include/prefix_tree.h"

#define ALPHABET_SIZE 256



Tree* createTree() {

	Tree *tree = malloc(sizeof(Tree));
	if (!tree) {
		return NULL;
	}

	tree->root.value = NULL;
	tree->root.children = calloc(ALPHABET_SIZE, sizeof(TreeNode*));
	if (!tree->root.children) {
		free(tree);
		return NULL;
	}

	return tree;

}


bool treeInsert(Tree* tree, char *key, void *value) {

	TreeNode *node = &tree->root;
	char *c = NULL;
	
	for (c = key; *c; c++) {

		TreeNode *parent = node;
		node = node->children[(unsigned char)(*c)];

		if (!node) {
			node = malloc(sizeof(TreeNode));
			if (!node) {
				return true;
			}
			node->value = NULL;
			node->children = calloc(ALPHABET_SIZE, sizeof(TreeNode*));
			if (!node->children) {
				free(node);
				return true;
			}
			parent->children[(unsigned char)(*c)] = node;
		}

	}

	node->value = value;

	return false;

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


void treeDetach(Tree* tree, char *key) {

	TreeNode *node = &tree->root;
	char *c = NULL;

	for (c = key; *c; c++) {

		node = node->children[(unsigned char)(*c)];
		if (!node)
			return;

	}

	node->value = NULL;

}


void freeNodes(TreeNode *node, bool free_value) {

	if (node == NULL)
		return;
	
	if (free_value)
		free(node->value);
	
	TreeNode **children = node->children;

	int i;
	for (i = 0; i < ALPHABET_SIZE; i++)
		if (children[i] != NULL)
			freeNodes(children[i], free_value);

	free(children);
	free(node);

}


void clearTree(Tree *tree, bool free_values) {

	int i;
	for (i = 0; i < ALPHABET_SIZE; i++)
		if (tree->root.children[i] != NULL) {
			freeNodes(tree->root.children[i], free_values);
			tree->root.children[i] = NULL;
		}

}


void removeTree(Tree *tree, bool free_values) {
	clearTree(tree, free_values);
	free(tree);
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