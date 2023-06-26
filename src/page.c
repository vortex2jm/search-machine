#include "../include/page.h"
#include "../include/redBlackTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct page {
  char *pageName;
  Tree *outPages; // Esta estrutura também pode ser uma RBT
  Tree *inPages;  // Pensar detalhe de implementação
  int outPagesSize;
  int inPagesSize;
  double pageRank;
};

//===================================//
Page *createPage(char *pageName) {
  Page *newPage = malloc(sizeof(Page));
  newPage->pageName = strdup(pageName);
  newPage->inPages = NULL;
  newPage->outPages = NULL;
  newPage->inPagesSize = 0;
  newPage->outPagesSize = 0;
  newPage->pageRank = 0;
  return newPage;
}

//===================================//
double getPageRank(Page *p) { return p->pageRank; }

//===================================//
void setPageRank(Page *p, double pr) { p->pageRank = pr; }

//===================================//
char *getPageName(Page *p) { return p->pageName; }

//=============================================//
Tree * getPagesIn(Page * p){ return p->inPages; }

//=============================================//
Tree * getPagesOut(Page * p){ return p->outPages; }

//=============================================//
void setPagesOut(Page * p, Tree * node){ p->outPages = node; }

//=============================================//
void setPagesIn(Page * p, Tree * node){ p->inPages = node; }

//=============================================//
void setPagesInSize(Page * p){ p->inPagesSize += 1; }

//=============================================//
void setPagesOutSize(Page * p, int size){ p->outPagesSize = size; }

//===================================//
int pageComparatorByPageRanking(void *p1, void *p2) {
  Page *pg1 = p1;
  Page *pg2 = p2;

  if (pg1->pageRank < pg2->pageRank)
    return -1;
  if (pg1->pageRank == pg2->pageRank)
    return 0;
  return 1;
}

//===========================================//
int pageComparatorByName(void * p1, void * p2){
  Page *pg1 = p1;
  Page *pg2 = p2;
  return strcasecmp(pg1->pageName, pg2->pageName);
}

//========================//
void printPage(void * page, void * argument){
  Page * pg = treeGetValue((Tree*)page);
  // Page * pg = page;
  printf("Page name: %s ; Page rank = %lf, outPages = %d\n", pg->pageName, pg->pageRank, pg->outPagesSize);
}

//===================================//
void freePage(Page *p) {
  if (p) {
    if (p->inPages) {
      free(p->inPages); //Os ponteiros dessa árvore serão desalocados na árvore principal (são cópias)
    }
    if (p->outPages) {
      free(p->outPages);  //Os ponteiros dessa árvore serão desalocados na árvore principal (são cópias)
    free(p);
    }
  }
}

//==============================================//
void calculatePageRank(Page * p, void * argument){
  int pagesAmount = ((int*)argument)[0];
  int difference = ((int*)argument)[1];

  
}

void getSumPageRank(Page * p, void * argument){
  
}
