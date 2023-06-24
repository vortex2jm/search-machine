#include "../include/page.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct page {
  char *pageName;
  Page **outPages; // Esta estrutura também pode ser uma RBT
  Page **inPages;  // Pensar detalhe de implementação
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
// Para ser utilizada no heap binario ( fila de prioridade)
int pageComparator(Page *p1, Page *p2) {
  if (p1->pageRank < p2->pageRank)
    return -1;
  if (p1->pageRank == p2->pageRank)
    return 0;
  return 1;
}

//===================================//
void freePage(Page *p) {
  if (p) {
    if (p->inPages) {
      for (int x = 0; x < p->inPagesSize; x++) {
        free(p->inPages[x]);
      }
      free(p->inPages);
    }
    if (p->outPages) {
      for (int x = 0; x < p->outPagesSize; x++) {
        free(p->outPages[x]);
      }
      free(p->outPages);
    }
    free(p);
  }
}
