#ifndef TERMSTREE_H
#define TERMSTREE_H

#include "../include/redBlackTree.h"
#include "../include/page.h"

typedef Tree termsTree; 

termsTree* termsTreeInsert(termsTree* node, char* key, Tree* value, Page* p);

termsTree* termsTreeSearch(Tree* root, char* key);

void* termsTreeGetValue(termsTree* node);

void termsTreeFree(termsTree* root);

#endif 
