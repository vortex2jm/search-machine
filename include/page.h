#ifndef PAGE_H
#define PAGE_H

#include <stdio.h>
#include <stdlib.h>
#include "redBlackTree.h"

#define ALPHA 0.85


typedef struct page Page;

Page *createPage(char *page_name);

double getPageRank(Page *p);

void setPageRank(Page *p, double pr);

double getLastPageRank(Page *p);

void setLastPageRank(Page *p, double pr);

char *getPageName(Page *p);

Tree * getPagesIn(Page * p);

Tree * getPagesOut(Page * p);

void setPagesOut(Page * p, Tree * node);

void setPagesIn(Page * p, Tree * node);

void setPagesInSize(Page * p);

void setPagesOutSize(Page * p, int size);

void printPage(void * page, void * argument);

int pageComparatorByName(void * p1, void * p2);

int pageComparatorByPageRanking(void *p1, void *p2);

void freePage(Page *p);

void calculatePageRank(Page * p, void * argument);

void getSumPageRank(Page * p, void * argument);

#endif
