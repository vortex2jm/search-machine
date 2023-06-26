#ifndef STOPWORDSTREE_H
#define STOPWORDSTREE_H

#include "../include/redBlackTree.h"

typedef Tree stopWordTree; 

stopWordTree* stopWordTreeInsert(stopWordTree* node, char* key);

stopWordTree* stopWordTreeSearch(stopWordTree* root, char* key);

char* stopWordTreeGetValue(stopWordTree* node);

void stopWordTreeFree(stopWordTree* root);


#endif