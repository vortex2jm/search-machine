#include "../include/page.h"
#include "../include/redBlackTree.h"
#include "../include/searchMachine.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  // Validation =============//
  if (argc < 2) {
    printf("You must insert main directory name!\n");
    return 1;
  }

  // Variables=================//
  int pagesAmount = 0;
  char *mainDir = strdup(argv[1]);

  // Construindo árvore de páginas
  PagesTree *pages = buildPagesTree(mainDir, &pagesAmount);

  // Inserindo links entre páginas
  linkPages(pages, mainDir);

  // Calculando page ranking
  pageRanking(pagesAmount, pages);

  // Construindo árvore de stop words
  StopWordTree *stopWords = buildStopWordsTree(mainDir);

  // Construindo árvore de termos
  TermsTree *terms = buildTermsTree(pages, stopWords, mainDir);

  // Consult processing======//
  searchProcessor(terms, stopWords, pagesAmount);

  // Dealloc ================//
  treeFree(terms, termTreeFreePagesTree);
  treeFree(stopWords, NULL);
  treeFree(pages, freePage);
  free(mainDir);

  return 0;
}
