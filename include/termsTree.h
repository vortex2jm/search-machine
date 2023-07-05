#ifndef TERMSTREE_H
#define TERMSTREE_H

#include "../include/page.h"
#include "../include/ternarySearchTries.h"

typedef Tree termsTree; 

void* termsTreeGetValue(termsTree* node);

int termsTreeCompare(void* c1, void* c2);

void termTreePrintNode(void* value, void* arg);

void termTreeFreePagesTree(void* value); 

#endif 