#ifndef PAGE_H
#define PAGE_H

#include <stdio.h>
#include <stdlib.h>
typedef struct page Page;

Page *createPage(char *page_name);

double getPageRank(Page *p);

void setPageRank(Page *p, double pr);

char *getPageName(Page *p);

void printPage(void * page);

int pageComparator(void *p1, void *p2);

void freePage(Page *p);

#endif
