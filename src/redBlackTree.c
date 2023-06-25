
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

Tree* treeCreateNode(char *key, void *value, bool color){
  Tree* newNode = malloc(sizeof(Tree));
  newNode->color = color;
  newNode->key = strdup(key);
  newNode->value = value;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}

// funções auxiliares
static bool isRed(Tree *node) {
  if (node == NULL)
    return BLACK;
  return node->color;
}

static void colorFlip(Tree *node) {
  node->color = RED;
  node->left->color = BLACK;
  node->right->color = BLACK;
}

static Tree *rotateRight(Tree *node) {
  Tree *aux = node->left;
  node->left = aux->right;
  aux->right = node;
  aux->color = aux->right->color;
  aux->right->color = RED;
  return aux;
}

static Tree *rotateLeft(Tree *node) {
  Tree *aux = node->right;
  node->right = aux->left;
  aux->left = node;
  aux->color = aux->left->color;
  aux->left->color = RED;
  return aux;
}

Tree* treeInsert(Tree *node, char *key, void *value) {
  // Insert at bottom and color it red.
  if (node == NULL) { return treeCreateNode(key, value, RED); }
  int cmp = strcasecmp(key, node->key);

  if (cmp < 0) { node->left = treeInsert(node->left, key, value); } 
  else if (cmp > 0) { node->right = treeInsert(node->right, key, value); }
  else { node->value = value; } 

  // Lean left.
  if (isRed(node->right) && !isRed(node->left)) { node = rotateLeft(node); }
  // Balance 4-node.
  if (isRed(node->left) && isRed(node->left->left)) { node = rotateRight(node);}
  // Split 4-node.
  if (isRed(node->left) && isRed(node->right)) { colorFlip(node); }
  return node;
}

Tree* treeSearch(Tree* root, char* key) {
  while (root != NULL) {
    int cmp = strcasecmp(key, root->key);
    if (cmp < 0) root = root->left;
    else if (cmp > 0) root = root->right;
    else return root;
  }
  
  return NULL;
}

void* treeGetValue(Tree* node){
  return node->value;
}

void treeFree(Tree* root){
  if(root != NULL){
    treeFree(root->left);
    treeFree(root->right);
    free(root->key);
    free(root);
  }
}