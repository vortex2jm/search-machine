#ifndef STOPWORDSTREE_H
#define STOPWORDSTREE_H

#include "../include/ternarySearchTries.h"

typedef Tree stopWordTree;

int stopWordsCompare(void* c1, void* c2);

void printStopWord(void* node, void* arg);

#endif