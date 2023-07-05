#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "../include/ternarySearchTries.h"

#define NULL_KEY NULL
#define NULL_VALUE NULL
#define RED true
#define BLACK false

struct node {
    unsigned char key;
    void* value;
    Tree *left, *middle, *right;
};

typedef struct string String;

struct string{
    unsigned char* c;
    int len;
};

// Implementação=======================//
//==========================================================================//
Tree* create_node(){
    Tree* node = malloc(sizeof(Tree));
    node->key = '\0';
    node->left = NULL;
    node->middle = NULL;
    node->right = NULL;
    node->value = NULL;
    return node;
}

static Tree* rec_insert(Tree* node, String* key, void* value, int d){
    unsigned char c = tolower(key->c[d]);
    //comparação deve ser revisada
    //int cmp = function(c, node->key);

    if (node == NULL) { node = create_node(); node->key = c;}
    if (c < node->key) { node->left = rec_insert(node->left, key, value, d); }
    else if (c > node->key) {node->right = rec_insert(node->right, key, value, d); }
    else if (d < key->len - 1) { node->middle = rec_insert(node->middle, key, value, d+1);
    } else { node->value = value; }
    return node;
}

Tree *treeInsert(Tree* node, char* key, void* value){
    String nKey;
    nKey.c = key;
    nKey.len = strlen(key);
    return rec_insert(node, &nKey, value, 0);
}

Tree* rec_search(Tree* node, String* key, int d) {
    if (node == NULL) { return NULL; }

    unsigned char c = tolower(key->c[d]);

    if (c < node->key) { return rec_search(node->left, key, d); }
    else if (c > node->key) { return rec_search(node->right, key, d); }
    else if (d < key->len - 1) {
        return rec_search(node->middle, key, d+1);
    } else { return node; }
}

void* treeSearch(Tree* node, char* key) {
    String nKey;
    nKey.c = key; nKey.len = strlen(key);
    node = rec_search(node, &nKey, 0);
    if (node == NULL) { return NULL; }
    else { return node->value; }
}


void treeFree(Tree *root, DeallocCallback function){
    if(root){
        treeFree(root->left,function);
        treeFree(root->middle,function);
        treeFree(root->right,function);
        if(function){
            function(root->value);
        }
        free(root);
    }
}


void treeTraversalInOrder(Tree *node, TraversalCallback function, void *argument){
    if(!node){return;}
    treeTraversalInOrder(node->left,function,argument);
    if(node->value != NULL){
        function(node, argument);
    }
    treeTraversalInOrder(node->middle,function,argument);
    treeTraversalInOrder(node->right,function,argument);
}


void *treeGetValue(Tree *node){
    return node->value;
}
