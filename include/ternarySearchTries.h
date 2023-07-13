#ifndef TREE_H
#define TREE_H

#include <stdbool.h>
#include <string.h>

// Para melhorar a legibilidade
typedef struct node Tree;
typedef Tree StopWordTree;
typedef Tree TermsTree;
typedef Tree PagesTree;

// protótipo das funções de callback
typedef void (*DeallocCallback)(void *value);
typedef int (*CompareCallback)(void *v1, void *v2);
typedef void (*TraversalCallback)(void *value, void *argument);

/// @brief obtem valor de um nó 
/// @param node nó de uma árvore
/// @return valor que está em node
void *treeGetValue(Tree *node);

/// @brief procura um nó na árvore através de uma chave
/// @param root raiz da árvore
/// @param key chave de busca
/// @return valor dentro do nó, se estiver lá. Se não estiver, retorna NULL
void *treeSearch(Tree *root, char *key);

/// @brief Libera memória alocada para uma árvore
/// @param root raiz da árvore
/// @param function callback para desalocar o tipo específico
void treeFree(Tree *root, DeallocCallback function);

/// @brief percorre árvore de forma ordenada
/// @param node raiz da árvore
/// @param function define o que deve ser feito ao longo da travessia
/// @param argument parâmetros de function
void treeTraversalInOrder(Tree *node, TraversalCallback function, void *argument);

/// @brief insere novo nó na árvore
/// @param node raiz da árvore
/// @param key chave a ser inserida
/// @param value valor a ser inserido
/// @return a raiz da árvore, pós inserção
Tree *treeInsert(Tree *node, char *key, void *value);

#endif
