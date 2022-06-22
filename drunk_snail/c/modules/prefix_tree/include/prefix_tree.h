#pragma once



typedef struct TreeNode {
	void *value;
	struct TreeNode **children;
} TreeNode;

typedef struct {
	TreeNode root;
} Tree;


Tree* createTree();

void treeInsert(Tree* tree, char *key, void *value);
void treeRemove(Tree* tree, char *key);

void freeNodes(TreeNode *node);
void clearTree(Tree *tree);

void* treeGet(TreeNode *node, char *key);
void* treeGetUnterminated(TreeNode *node, char *key, size_t length);

void* dictionaryLookup(Tree *tree, char *key);
void* dictionaryLookupUnterminated(Tree *tree, char *key, size_t length);