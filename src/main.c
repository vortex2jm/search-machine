#include "../include/page.h"
#include "../include/redBlackTree.h"
#include "../include/searchMachine.h"
#include "../include/stopWordsTree.h"
#include "../include/util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  // Validation =============//
  if (argc < 2) {
    printf("You must insert main directory name!\n");
    return 1;
  }

  //=================//
  int pagesAmount = 0;
  char *mainDir = strdup(argv[1]);

  // Construindo árvore de páginas
  pagesTree *pages = buildPagesTree(mainDir, &pagesAmount);
  //treeTraversalInOrder(pages, printPage, NULL); // For debug

  // Inserindo links entre páginas
  linkPages(pages, mainDir);
  //treeTraversalInOrder(pages, printOut, NULL); // For debug

  // Calculando page ranking
  pageRanking(pagesAmount, pages);
  //treeTraversalInOrder(pages, printPage, NULL);

  //====================================================//
  // Construindo árvore de stop words
  stopWordTree *stopwords = buildStopWordsTree(mainDir);
  //treeTraversalInOrder(stopwords, printStopWord, NULL); // For debug

  // TODO: create terms symbol table, must think about implementation
  //====================================================//
  termsTree* terms = buildTermsTree(pages, stopwords, mainDir);
  // Consult reading=========//

  // Consult processing======//

  // Dealloc ================//
  treeFree(pages, freePage);
  treeFree(stopwords, NULL);
  free(mainDir);

  return 0;
}
