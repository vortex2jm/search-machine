#ifndef PAGE_H
#define PAGE_H

#include "redBlackTree.h"
#include <stdio.h>
#include <stdlib.h>

#define ALPHA 0.85

typedef struct page Page;

// Destrói Página
void freePage(void *p);

// Coleta PagesIn
Tree *getPagesIn(Page *p);

// Coleta PageName
char *getPageName(Page *p);

// Coleta PagesOut
Tree *getPagesOut(Page *p);

// Coleta PageRank
double getPageRank(Page *p);

// Troca PagesInSize
void setPagesInSize(Page *p);

// Coleta LastPageRank
double getLastPageRank(Page *p);

// Cria uma Página com nome definido
// ponteiros NULOS e valores zerados
Page *createPage(char *page_name);

// Troca PageRank
void setPageRank(Page *p, double pr);

// Troca PagesIn
void setPagesIn(Page *p, Tree *node);

// => PagesOut
void setPagesOut(Page *p, Tree *node);

// Troca PagesOutSize
void setPagesOutSize(Page *p, int size);

// Troca LastPageRank
void setLastPageRank(Page *p, double pr);

// Função auxiliar
void printPage(void *page, void *argument);

// Comparador de Páginas por Nome
int pageComparatorByName(void *k1, void *k2);

// Move PageRank para LastPageRank
void updatePageRank(void *page, void *argument);

// Calcula a parte de soma para o calculo de PageRanking
void getSumPageRank(void *page, void *argument);

// Calcula um ciclo de atualização do PageRanking
void calculatePageRank(void *page, void *argument);

// Comparador de Páginas por PageRanking
int pageComparatorByPageRanking(void *p1, void *p2);

// Troca os valores do vetor para NULL
void setPageVector(Page **vector, int size);

#endif
