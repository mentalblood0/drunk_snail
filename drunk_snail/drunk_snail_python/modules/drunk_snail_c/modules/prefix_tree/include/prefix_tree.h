#pragma once


#include <stdbool.h>



typedef struct TreeNode {
	void *value;
	struct TreeNode **children;
} TreeNode;

typedef struct {
	TreeNode root;
} Tree;


Tree* createTree();

bool treeInsert(Tree* tree, char *key, void *value);
void treeRemove(Tree* tree, char *key);
void treeDetach(Tree* tree, char *key);

void freeNodes(TreeNode *node);
void clearTree(Tree *tree);
void removeTree(Tree *tree);

void* treeGet(TreeNode *node, char *key);
void* treeGetUnterminated(TreeNode *node, char *key, size_t length);

void* dictionaryLookup(Tree *tree, char *key);
void* dictionaryLookupUnterminated(Tree *tree, char *key, size_t length);