#ifndef TERMSTREE_H
#define TERMSTREE_H

#include "../include/page.h"
#include "../include/redBlackTree.h"

typedef Tree termsTree; 

void* termsTreeGetValue(termsTree* node);

termsTree* termsTreeSearch(Tree* root, char* key);

termsTree* termsTreeInsert(termsTree* node, char* key, Page* value, int compareMode);

// void termsTreeFree(termsTree* root);

#endif 
