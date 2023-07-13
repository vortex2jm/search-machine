#ifndef PAGE_H
#define PAGE_H

#include "ternarySearchTries.h"
#include <stdio.h>
#include <stdlib.h>

#define ALPHA 0.85

typedef struct page Page;

/// @brief libera a memória da página, dentro de uma callback TST
/// @param p deve ser um Page*
void freePage(void *p);

/// @brief obtém PagesIn de uma página
/// @param p página de interesse
/// @return árvore de páginas IN
Tree *getPagesIn(Page *p);

/// @brief obtém o nome da página 
/// @param p página de interesse
/// @return nome da página
char *getPageName(Page *p);

/// @brief obtém PagesOut de uma página
/// @param p página de interesse
/// @return árvore de páginas OUT
Tree *getPagesOut(Page *p);

/// @brief obtém PageRank de uma página
/// @param p página de interesse
/// @return PageRank
double getPageRank(Page *p);

/// @brief incrementa numero da paginas IN de uma página
/// @param p página de interesse
void setPagesInSize(Page *p);

/// @brief obtém PageRank calculado anteriormente
/// @param p página de interesse
/// @return último PageRank calculado
double getLastPageRank(Page *p);

/// @brief cria uma nova página
/// @param page_name nome da página
/// @return página criada
Page *createPage(char *page_name);

/// @brief define novo PageRank
/// @param p páginad de interesse
/// @param pr novo PageRank
void setPageRank(Page *p, double pr);

/// @brief obtém contador de interseção
/// @param p página de interesse
/// @return contador
int getIntersectionCounter(Page * p);

/// @brief Substitui conjunto de páginas IN
/// @param p página de interesse
/// @param node raiz da nova árvore
void setPagesIn(Page *p, Tree *node);

//equivalente de setPagesIn => PagesOut
void setPagesOut(Page *p, Tree *node);

/// @brief troca tamanho do conjunto de páginas OUT
/// @param p página de interesse
/// @param size novo tamanho
void setPagesOutSize(Page *p, int size);

/// @brief troca LastPageRank
/// @param p página de interesse
/// @param pr novo LastPageRank
void setLastPageRank(Page *p, double pr);

/// @brief auxiliar para imprimir página
/// @param page página a ser impressa
/// @param argument
void printPage(void *page, void *argument);

/// @brief compara duas páginas por nome
/// @param k1 nome da pagina 1
/// @param k2 nome da pagina 2
/// @return resultado da comparação
int pageComparatorByName(void *k1, void *k2);

/// @brief move pageRank para LastPageRank
/// @param page página de interesse
/// @param argument 
void updatePageRank(void *page, void *argument);

/// @brief calcula a parte de soma para o calculo de PageRanking
/// @param page página de interesse
/// @param argument 
void getSumPageRank(void *page, void *argument);

/// @brief calcula um ciclo de atualização do PageRanking
/// @param page página de interesse
/// @param argument 
void calculatePageRank(void *page, void *argument);

/// @brief compara páginas por PageRanking
/// @param p1 página 1
/// @param p2 página 2
/// @return resultado da comparação
int pageComparatorByPageRanking(void *p1, void *p2);

/// @brief callback do processador de consultas
/// @param value 
/// @param argument
void intersectionProcessor(void * value, void * argument);

/// @brief comparador de páginas para o quicksort
/// @param p1 página 1
/// @param p2 página 2
/// @return resultado da comparação
int comparatorPagesVector(const void *p1, const void *p2); 

/// @brief gerador de saídas das consultas
/// @param buffer busca realizada pelo usuário
/// @param pagesVector vetor com as páginas que apareceram
/// @param pagesVectorSize tamanho do vetor
/// @param intersectionRange quantidade máxima da interseção
void printConsult(char * buffer, Page ** pagesVector, int pagesVectorSize, int intersectionRange);

#endif
