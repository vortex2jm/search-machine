#ifndef PAGE_H
#define PAGE_H

#include <stdio.h>
#include <stdlib.h>
typedef struct page Page;

Page* createPage(FILE* inputFile, double pageRank);

FILE* getFile(Page* p);

double getPageRank(Page* p);

char* getPageName(Page* p);

void freePage(Page* p);

#endif