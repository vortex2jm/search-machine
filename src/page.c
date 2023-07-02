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
  int intersectionCounter;
  double pageRank;
  double lastPageRank;
};

// Protótipos===================//
void freePage(void *p);
Tree *getPagesIn(Page *p);
Tree *getPagesOut(Page *p);
char *getPageName(Page *p);
double getPageRank(Page *p);
void setPagesInSize(Page *p);
double getLastPageRank(Page *p);
Page *createPage(char *pageName);
void setPageRank(Page *p, double pr);
void setPagesOutSize(Page *p, int size);
void setLastPageRank(Page *p, double pr);
void printPage(void *page, void *argument);
int pageComparatorByName(void *k1, void *k2);
void getSumPageRank(void *page, void *argument);
void updatePageRank(void *page, void *argument);
void calculatePageRank(void *page, void *argument);
int pageComparatorByPageRanking(void *p1, void *p2);

// Implementação================//
//==============================//
Page *createPage(char *pageName) {
  Page *newPage = malloc(sizeof(Page));
  newPage->pageName = strdup(pageName);
  newPage->inPages = NULL;
  newPage->outPages = NULL;
  newPage->inPagesSize = 0;
  newPage->outPagesSize = 0;
  newPage->pageRank = 0;
  newPage->lastPageRank = 0;
  newPage->intersectionCounter = 0;
  return newPage;
}

//================================================//
double getPageRank(Page *p) { return p->pageRank; }

//========================================================//
void setPageRank(Page *p, double pr) { p->pageRank = pr; }

//=========================================================//
double getLastPageRank(Page *p) { return p->lastPageRank; }

//==============================================================//
void setLastPageRank(Page *p, double pr) { p->lastPageRank = pr; }

//=============================================//
char *getPageName(Page *p) { return p->pageName; }

//=============================================//
Tree *getPagesIn(Page *p) { return p->inPages; }

//=============================================//
Tree *getPagesOut(Page *p) { return p->outPages; }

//===========================================================//
int getIntersectionCounter(Page * p){ return p->intersectionCounter; }

//===========================================================//
void setPagesOut(Page *p, Tree *node) { p->outPages = node; }

//=========================================================//
void setPagesIn(Page *p, Tree *node) { p->inPages = node; }

//==================================================//
void setPagesInSize(Page *p) { p->inPagesSize += 1; }

//================================================================//
void setPagesOutSize(Page *p, int size) { p->outPagesSize = size; }

//==================================================//
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
int pageComparatorByName(void *k1, void *k2) {
  char *key1 = k1;
  char *key2 = k2;
  return strcasecmp(key1, key2);
}

//=========================================//
void printPage(void *page, void *argument) {
  Page *pg = treeGetValue((Tree *)page);
  // Page * pg = page;
  printf("Page name: %s ; Page rank = %.16lf, outPages = %d\n", pg->pageName,
         pg->pageRank, pg->outPagesSize);
}

//=====================//
void freePage(void *page) {
  Page *p = page;
  if (p) {
    if (p->pageName) {
      free(p->pageName);
    }
    if (p->inPages) {
      treeFree(p->inPages, NULL); // Os ponteiros dessa árvore serão desalocados
                                  // na árvore principal (são cópias)
    }
    if (p->outPages) {
      treeFree(p->outPages,
               NULL); // Os ponteiros dessa árvore serão desalocados na árvore
                      // principal (são cópias)
    }
    free(p);
  }
}

//=================================================//
void calculatePageRank(void *page, void *argument) {
  Page *p = (treeGetValue((Tree *)page));

  double pagesAmount = ((double *)argument)[0];
  double difference = ((double *)argument)[1];

  double pr = 0.0;

  treeTraversalInOrder(p->inPages, getSumPageRank, &pr);

  if (p->outPagesSize == 0) {
    pr += getLastPageRank(p);
  }

  pr *= ALPHA;
  pr += (1 - ALPHA) / pagesAmount;

  setPageRank(p, pr);

  if ((pr < getLastPageRank(p))) { // Calcular variação
    difference -= (pr - getLastPageRank(p));
  } else {
    difference += (pr - getLastPageRank(p));
  }

  double *vetor = (double *)argument;

  vetor[1] = difference;
}

//==============================================//
void getSumPageRank(void *page, void *argument) {
  Page *p = (treeGetValue((Tree *)page));
  double *sum = (double *)argument;
  *sum += p->lastPageRank / p->outPagesSize;
}

//==============================================//
void updatePageRank(void *page, void *argument) {
  Page *p = (treeGetValue((Tree *)page));
  setLastPageRank(p, getPageRank(p));
}

//=========================================//
void setPageVector(Page **vector, int size) {
  for (int i = 0; i < size; i++) {
    vector[i] = NULL;
  }
}

//=========================================//
int comparatorPagesVector(const void *p1, const void *p2){
  Page* castP1 = (Page*)p1;
  Page* castP2 = (Page*)p2;

  if(castP1 == NULL && castP2 == NULL){
    return 0;
  }
  else if(castP1 == NULL){
    return 1;
  }
  else if(castP2 == NULL){
    return -1;
  }

  return castP1->pageRank - castP2->pageRank;

}

//========================IMPLEMENTANDO AINDA COM ERRO========================//
//==================================================//
void intersectionProcessor(void * value, void * argument){
  //================ CASTING FUCKFEST ====================//
  void ** pagesIntersectionArguments =  (void**) argument;
  Page** pages = (Page**)pagesIntersectionArguments[0];
  int* index = (int*)pagesIntersectionArguments[1];
  Page * p = value;

  if(pages[0] == NULL)
    printf("CORO E COÇA\n"); 
  printf("index %d\n", *index); 

  //Logica
  // if(!p->intersectionCounter){
  //   pages[*index] = p;
  //   *index++;
  //   p->intersectionCounter++;
  //   return;
  // }
  // p->intersectionCounter++;
}

//==================================================//
void printConsult(char * buffer, Page ** pagesVector, int intersectionRange){
  printf("search:%s", buffer);
  printf("pages:");
  
  Page * p=NULL;
  int x=0;
  while((p = pagesVector[x])){
    if(getIntersectionCounter(pagesVector[x]) == intersectionRange){
      printf("%s ", p->pageName);
    }
    x++;
  }
  printf("\n");
  printf("pr:");

  x=0;
  while((p = pagesVector[x])){
    if(getIntersectionCounter(pagesVector[x]) == intersectionRange){
      printf("%lf ", p->pageRank);
      p = NULL;
    }
    x++;
  }
  printf("\n");
}
//==========================================================================//