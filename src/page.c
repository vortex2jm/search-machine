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

//===================================//
int pageComparator(void *p1, void *p2) {
  Page *pg1 = p1;
  Page *pg2 = p2;

  if (pg1->pageRank < pg2->pageRank)
    return -1;
  if (pg1->pageRank == pg2->pageRank)
    return 0;
  return 1;
}

//========================//
void printPage(void * page){
  Page * pg = page;
  printf("Page name: %s ; Page rank = %lf\n", pg->pageName, pg->pageRank);
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
