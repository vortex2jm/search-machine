#include <stdio.h>
#include <stdlib.h>

#include "../include/redBlackTree.h"

#define NULL_KEY NULL
#define NULL_VALUE NULL
#define RED true
#define BLACK false

struct node{
    char* word;
    Heap* pages;
    bool color;
    RBT* left; 
    RBT* right;
};

// funções auxiliares 
static bool isRed(RBT* node){
    if(node == NULL) return BLACK;
    return node->color;
}

static void colorFlip(RBT* node){
    node->color = RED;
    node->left->color = BLACK;
    node->right->color = BLACK;
}

static RBT* rotateRight(RBT* node){
    RBT* aux = node->left;
    node->left = aux->right;
    aux->right = node;
    aux->color = aux->right->color;
    aux->right->color = RED;
    return aux;
}

RBT* rotateLeft(RBT* node){
    RBT* aux = node->right;
    node->right = aux->left;
    aux->left = node;
    aux->color = aux->left->color;
    aux->left->color = RED;
    return aux;
}

RBT* rbtCreateNode(char* word, Heap* pages, bool color, int maxPages){
    RBT* new = malloc(sizeof(RBT));
    new->word = strdup(word);
    new->pages = heapInit(maxPages);
    new->color = BLACK;
    new->right = NULL;
    new->left = NULL;
    return new;
}

Heap* rbtSearch(RBT* root, char* key) {
    return recursiveSearch(root, key);
}

static Heap* recursiveSearch(RBT* node, char* key) {
    if (node == NULL) { return NULL_VALUE; }
    int cmp = strcasecmp(key, node->word);
    
    if (cmp < 0) { return rec_get(node->left, key); }
    else if (cmp > 0) { return rec_get(node->right, key); }
    else /*cmp == 0*/ { return node->pages; }
}

RBT* RBT_insert(RBT *node, char* key, Page* value, int maxPages) {
    // Insert at bottom and color it red.
    if (node == NULL) { return rbtCreateNode(key, value, RED, maxPages); }
    int cmp = compare(key, node->word);
    
    if (cmp < 0) { node->left = RBT_insert(node->left, key, value, maxPages); }
    else if (cmp > 0) { node->right = RBT_insert(node->right, key, value, maxPages); }
    else /*cmp == 0*/ { node->pages = value; } //heap insertion
    
    // Lean left.
    if (isRed(node->right) && !isRed(node->left)) { node = rotateLeft(node); }
    // Balance 4-node.
    if (isRed(node->left) && isRed(node->left->left)) { node = rotateRight(node); }
    // Split 4-node.
    if (isRed(node->left) && isRed(node->right)) { colorFlip(node); }
    return node;
}    



