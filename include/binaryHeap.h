#ifndef BINARYHEAP_H
#define BINARYHEAP_H

#include "../include/page.h"

typedef struct heap Heap;

Heap* heapInit(int maxN); 
void heapInsert(Page* p);   
Page* heapDelMin();       
void PQ_decrease_key(int id, double value); 

#endif