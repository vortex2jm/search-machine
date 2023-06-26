#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "../include/redBlackTree.h"

#define NULL_KEY NULL
#define NULL_VALUE NULL
#define RED true
#define BLACK false

struct node{
  char *key;
  void *value;
  bool color;
  Tree *left, *right;
};

// Prototypes==========================================//
bool isRed(Tree *node);
void treeFree(Tree* root);
void colorFlip(Tree *node);
Tree *rotateLeft(Tree *node); 
Tree *rotateRight(Tree *node);
void* treeGetValue(Tree* node);
Tree* treeSearch(Tree* root, char* key);
Tree* treeCreateNode(char* key, void* value, bool color);
void treeTraversalInOrder(Tree * node, TraversalCallback function);
Tree* treeInsert(Tree* node, char* key, void* value, CompareCallback function);

// Implementation =====================================//
//=====================================================//

// Vai precisar adicionar uma callback nessa função para comparar os nós
//TODO: COLOCAR CALLBACK
Tree* treeInsert(Tree* node, char* key, void* value, CompareCallback function){
  // Insert at bottom and color it red.
  if (node == NULL) { return treeCreateNode(key, value, RED); }
  int cmp = function(key, node->key);

  if (cmp < 0) { node->left = treeInsert(node->left, key, value, function); } 
  else if (cmp > 0) { node->right = treeInsert(node->right, key, value, function); }
  else { node->value = value; } 

  // Lean left.
  if (isRed(node->right) && !isRed(node->left)) { node = rotateLeft(node); }
  // Balance 4-node.
  if (isRed(node->left) && isRed(node->left->left)) { node = rotateRight(node);}
  // Split 4-node.
  if (isRed(node->left) && isRed(node->right)) { colorFlip(node); }
  return node;
}

//======================================//
Tree* treeSearch(Tree* root, char* key) {
  while (root != NULL) {
    int cmp = strcasecmp(key, root->key);
    if (cmp < 0) root = root->left;
    else if (cmp > 0) root = root->right;
    else return root;
  }
  
  return NULL;
}

//============================//
void* treeGetValue(Tree* node){
  return node->value;
}

//======================================================//
//TODO: COLOCAR CALLBACK
void treeTraversalInOrder(Tree * node, TraversalCallback function){
  if(!node){
    return;
  }
  
  treeTraversalInOrder(node->left, function);
  function(node);
  treeTraversalInOrder(node->right, function);
}

//=======================//
void treeFree(Tree* root){
  if(root != NULL){
    treeFree(root->left);
    treeFree(root->right);
    free(root->key);
    free(root);
  }
}

//===============================//
// funções auxiliares
//===============================//
//=====================================================//
Tree* treeCreateNode(char *key, void *value, bool color){
  Tree* newNode = malloc(sizeof(Tree));
  newNode->color = color;
  newNode->key = strdup(key);
  newNode->value = value;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}

//===========================//
bool isRed(Tree *node) {
  if (node == NULL)
    return BLACK;
  return node->color;
}

//=================================//
void colorFlip(Tree *node) {
  node->color = RED;
  node->left->color = BLACK;
  node->right->color = BLACK;
}

//===================================//
Tree *rotateRight(Tree *node) {
  Tree *aux = node->left;
  node->left = aux->right;
  aux->right = node;
  aux->color = aux->right->color;
  aux->right->color = RED;
  return aux;
}

//==================================//
Tree *rotateLeft(Tree *node) {
  Tree *aux = node->right;
  node->right = aux->left;
  aux->left = node;
  aux->color = aux->left->color;
  aux->left->color = RED;
  return aux;
}
