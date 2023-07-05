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
  Tree *castTree = (Tree*)node;
  Page *castPage = treeGetValue(castTree);
  double *PRDouble = PR;
  setPageRank(castPage, *PRDouble);
  setLastPageRank(castPage, *PRDouble);
}

//CONSERTAR BUG DE RESET DE BUSCA==========================//
//=========================================================//
void searchProcessor(termsTree *terms, stopWordTree *stopWords,
                     int pagesAmount) {
  //===================//
  int termsAmount = 0;  // Quantidade de termos
  size_t bufferSize = 0;  //auxiliar
  pagesTree *termPages = NULL;  // Árvore de páginas que contém o termo
  char *buffer = NULL, *search=NULL, * token = NULL;

  //Vetor de páginas que contém os termos===================================//
  // Este vetor foi alocado com a quantidade de páginas que tem na árvore
  // de páginas, mas não necessariamente todas elas estarão lá dentro
  Page **intersectionPages = calloc(pagesAmount, sizeof(Page *));
  int intersectionIndex = 0;  // próximo índice livre do vetor

  //Argumentos da callback==================================================//
  void ** pagesIntersectionArguments = malloc(sizeof(void*)*2);
  pagesIntersectionArguments[0] = intersectionPages;  //vetor
  pagesIntersectionArguments[1] = &intersectionIndex; //próximo índice livre

  //========================================================//
  while (getline(&buffer, &bufferSize, stdin) != -1) {
    // Copiando o conteudo do buffer para a variavel search pois o strtok modifica a variável buffer
    search = strdup(buffer);

    // Separando as strings da consulta
    token = strtok(buffer, " \n");
    while(token){
      if (!treeSearch(stopWords, token)) {
        // Garantindo que as palavras da cconsulta estarão na árvore, podemos retirar esta verificação
        if((termPages = treeSearch(terms, token))){
          // Atravessando a árvore de páginas que contém os termos e adicionando-as no vetor a ser ordenado
          // caso ainda não esteja lá e incrementando o contador de intersecção
          treeTraversalInOrder(termPages, intersectionProcessor, pagesIntersectionArguments);
        }
      }
      token = strtok(NULL, " \n");
      termsAmount++;  //Adicionando o contador de termos
    }
    
    // Ordenando o vetor de páginas
    qsort(intersectionPages, intersectionIndex, sizeof(Page*), comparatorPagesVector);
    printConsult(search, intersectionPages, intersectionIndex, termsAmount);
    intersectionIndex = 0;
    termsAmount = 0;
  }

  free(buffer);
  free(search);
  free(intersectionPages);
  free(pagesIntersectionArguments);
}
