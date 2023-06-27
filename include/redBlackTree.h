#ifndef TREE_H
#define TREE_H

#include <string.h>
#include <stdbool.h>

#define KEY_COMPARE 1
#define VALUE_COMPARE 0

typedef struct node Tree;

// funções que devem ser definidas pelo cliente
typedef void (*DeallocCallback)(void *value);
typedef int (*CompareCallback)(void *v1, void *v2);
typedef void (*TraversalCallback)(void *value, void *argument);

// Retorna a chave de uma árvore
char *treeGetKey(Tree *node);

// Retorna o valor de um nó da árvore 
void *treeGetValue(Tree *node);

// Procura um nó na árvore através de uma chave
Tree *treeSearch(Tree *root, char *key);

// Libera memória alocada para uma árvore. Usa uma função de callback para desalocar o valor
// Caso a função seja nula, desaloca só os nós da árvore
void treeFree(Tree *root, DeallocCallback function);

// Atravessa a árvore de forma crescente 
void treeTraversalInOrder(Tree *node, TraversalCallback function, void *argument);

// Insere um novo nó na árvore 
Tree *treeInsert(Tree *node, char *key, void *value, CompareCallback function, int compareMode);

#endif
