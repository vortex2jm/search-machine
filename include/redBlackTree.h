#ifndef TREE_H
#define TREE_H

#include <stdbool.h>
#include <string.h>

typedef struct node Tree;

//funções que devem ser definidas pelo cliente
typedef void (*TraversalCallback)(void * value, void * argument);
typedef int (*CompareCallback)(void * v1, void *v2); 

Tree* treeInsert(Tree* node, char* key, void* value, CompareCallback function);

Tree* treeSearch(Tree* root, char* key);

void* treeGetValue(Tree* node);

void treeTraversalInOrder(Tree * node, TraversalCallback function, void * argument);

void treeFree(Tree* root);

#endif
