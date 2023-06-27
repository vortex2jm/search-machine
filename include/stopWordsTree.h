#ifndef STOPWORDSTREE_H
#define STOPWORDSTREE_H

#include "../include/redBlackTree.h"

typedef Tree stopWordTree;


stopWordTree* stopWordTreeInsert(stopWordTree* node, char* key, int compareMode);

stopWordTree* stopWordTreeSearch(stopWordTree* root, char* key);

char* stopWordTreeGetValue(stopWordTree* node);

void stopWordtreeTraversalInOrder(stopWordTree *node);

char* stopWordGetValue(stopWordTree * node);

void stopWordTreeFree(stopWordTree* root);


#endif