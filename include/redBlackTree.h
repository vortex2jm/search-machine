#ifndef RBT_H
#define RBT_H

#include <stdbool.h>
#include <string.h>

#include "../include/binaryHeap.h"

typedef struct node RBT;

RBT* rbtCreateNode(char* word, Heap* pages, bool color, int maxPages);

Heap* rbtSearch(RBT* root, char* key);

RBT* RBT_insert(RBT *node, char* key, Page* value, int maxPages);

#endif