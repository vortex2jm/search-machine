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
  double lastPageRank;
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
  newPage->lastPageRank = 0;
  return newPage;
}

//===================================//
double getPageRank(Page *p) { return p->pageRank; }

//===================================//
void setPageRank(Page *p, double pr) { p->pageRank = pr; }

//===================================//
double getLastPageRank(Page *p) { return p->lastPageRank; }

//===================================//
void setLastPageRank(Page *p, double pr) { p->lastPageRank = pr; }

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
  printf("Page name: %s ; Page rank = %.16lf, outPages = %d\n", pg->pageName, pg->pageRank, pg->outPagesSize);
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
void calculatePageRank(void * page, void * argument){
  Page * p = (treeGetValue((Tree*) page));

  double pagesAmount = ((double*)argument)[0];
  double difference = ((double*)argument)[1];

  double pr = 0.0;

  treeTraversalInOrder(p->inPages,getSumPageRank,&pr);


  if(p->outPagesSize==0){
    pr += getLastPageRank(p);
  }

  pr *= ALPHA;
  pr += (1-ALPHA)/pagesAmount;

  setPageRank(p,pr);

  if((pr < getLastPageRank(p))){ //Calcular variação
  difference -= (pr - getLastPageRank(p));
  }else{
    difference += (pr - getLastPageRank(p));
  }

  double* vetor = (double*)argument;

  vetor[1] = difference;  
  
}

void getSumPageRank(void * page, void * argument){ 
  Page * p = (treeGetValue((Tree*) page));
  double* sum = (double*) argument;
  *sum += p->lastPageRank/p->outPagesSize;
}

void updatePageRank(void * page, void* argument){
  Page * p = (treeGetValue((Tree*) page));
  setLastPageRank(p,getPageRank(p));
}
