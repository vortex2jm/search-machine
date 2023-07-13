#include "../include/page.h"
#include "../include/ternarySearchTries.h"
#include "../include/searchMachine.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  // validação //
  if (argc < 2) {
    printf("You must insert main directory name!\n");
    return 1;
  }
  
  // variaveis //
  int pagesAmount = 0;
  char *mainDir = strdup(argv[1]);

  // Construindo árvore de páginas
  PagesTree *pages = buildPagesTree(mainDir, &pagesAmount);

  // Inserindo links entre páginas
  linkPages(pages, mainDir);

  // Calculando page ranking
  pageRanking(pagesAmount, pages);

  // Construindo árvore de stop words
  StopWordTree *stopwords = buildStopWordsTree(mainDir);

  // Construindo árvore de termos
  TermsTree *terms = buildTermsTree(pages, stopwords, mainDir);

  // processamento de consultas //
  searchProcessor(terms, stopwords, pagesAmount);

  // Dealloc ================//
  treeFree(terms, termTreeFreePagesTree);
  treeFree(stopwords, NULL);
  treeFree(pages, freePage);
  free(mainDir);

  return 0;
}