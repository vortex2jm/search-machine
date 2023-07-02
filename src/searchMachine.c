#include "../include/searchMachine.h"
#include "../include/page.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Protótipos================================//
void setPageRankCallback(void *node, void *PR);
void pageRanking(int pageAmount, pagesTree *pageTree);

// Implementação================================//
void pageRanking(int pageAmount, pagesTree *pageTree) {
  // Inicio de valor inicial
  double firstPR = 1.0 / (double)pageAmount;
  treeTraversalInOrder(pageTree, setPageRankCallback, &firstPR);

  double variables[2];
  variables[0] = (double)pageAmount;
  variables[1] = 1.0;

  // Atualização
  while (variables[1] >= PGR_LIMIT) {
    variables[1] = 0.0;
    treeTraversalInOrder(pageTree, calculatePageRank, variables);
    treeTraversalInOrder(pageTree, updatePageRank, NULL);
    variables[1] /= pageAmount;
  }
}

//============================================//
void setPageRankCallback(void *node, void *PR) {
  Tree *castTree = node;
  Page *castPage = treeGetValue(castTree);
  double *PRDouble = PR;
  setPageRank(castPage, *PRDouble);
  setLastPageRank(castPage, *PRDouble);
}

//==========================IMPLEMENTANDO AINDA COM ERRO================//
//=========================================================//
void searchProcessor(termsTree *terms, stopWordTree *stopWords,
                     int pagesAmount) {
  //===================//
  char *buffer = NULL;
  size_t bufferSize = 0;
  pagesTree *termPages = NULL;
  int termsAmount = 0;
  char * search=NULL;

  //=========================================================//
  Page **intersectionPages = calloc(pagesAmount, sizeof(Page *));
  int intersectionIndex = 0;

  //========================================================//
  void ** pagesIntersectionArguments = malloc(sizeof(void*)*2);
  pagesIntersectionArguments[0] = &intersectionPages;
  pagesIntersectionArguments[1] = &intersectionIndex;

  //========================================================//
  while (getline(&buffer, &bufferSize, stdin) != -1) {
    
    search = strdup(buffer);
    buffer = strtok(buffer, " \n");
    while(buffer){
      printf("conteudo do buffer = %s\n", buffer);

      if (treeSearch(stopWords, buffer, BY_KEY)) {
        continue;
      }

      termPages = treeSearch(terms, buffer, BY_VALUE);
      if (!termPages) {
        printf("ARVORE DE PAGINAS NULA NO TERMS TREE");
        continue;
      }

      treeTraversalInOrder(termPages, intersectionProcessor, pagesIntersectionArguments);
      buffer = strtok(NULL, " \n");
      termsAmount++;
    }
    
    qsort(intersectionPages, pagesAmount,sizeof(Page*),comparatorPagesVector);
    printConsult(search, intersectionPages, termsAmount);

    // unusable
    // setPageVector(intersectionPages, pagesAmount);
  }

  // Dar free no vetor de páginas
  free(buffer);
  free(search);
}
