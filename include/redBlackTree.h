#ifndef TREE_H
#define TREE_H

#include <stdbool.h>
#include <string.h>

typedef struct node Tree;
typedef void (*Callback)(void * value);

Tree* treeCreateNode(char* key, void* value, bool color);

Tree* treeInsert(Tree* node, char* key, void* value);

Tree* treeSearch(Tree* root, char* key);

void* treeGetValue(Tree* node);

void treeTraversalInOrder(Tree * node, Callback function);

void treeFree(Tree* root);

#endif
