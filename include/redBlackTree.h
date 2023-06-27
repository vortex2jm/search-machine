#ifndef TREE_H
#define TREE_H

#include <stdbool.h>
#include <string.h>

#define KEY_COMPARE 1
#define VALUE_COMPARE 0

typedef struct node Tree;

//funções que devem ser definidas pelo cliente
typedef void (*TraversalCallback)(void * value, void * argument);
typedef int (*CompareCallback)(void * v1, void *v2); 

Tree* treeInsert(Tree* node, char* key, void* value, CompareCallback function, int compareMode);

Tree* treeSearch(Tree* root, char* key);

void* treeGetValue(Tree* node);

Tree* getleftNode(Tree* node);

Tree* getRightNode(Tree* node);

void treeTraversalInOrder(Tree * node, TraversalCallback function, void * argument);

char* treeGetKey(Tree *node);

void treeFree(Tree* root);

#endif
