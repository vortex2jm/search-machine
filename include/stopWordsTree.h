#ifndef STOPWORDSTREE_H
#define STOPWORDSTREE_H

#include "../include/redBlackTree.h"

typedef Tree stopWordTree;

char* stopWordGetValue(stopWordTree * node);

char* stopWordTreeGetValue(stopWordTree* node);

void stopWordtreeTraversalInOrder(stopWordTree *node);

stopWordTree* stopWordTreeSearch(stopWordTree* root, char* key);

stopWordTree* stopWordTreeInsert(stopWordTree* node, char* key, int compareMode);

// void stopWordTreeFree(stopWordTree* root);

#endif
