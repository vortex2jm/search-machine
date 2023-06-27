#include "../include/page.h"
#include "../include/util.h"
#include "../include/redBlackTree.h"
#include "../include/stopWordsTree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  // Validation =============//
  if (argc < 2) {
    printf("You must insert main directory name!\n");
    return 1;
  }

  // Data reading============//
  int pagesAmount=0;
  char *mainDir = strdup(argv[1]);

  //building pages symbol table
  Tree * pageTree = readPages(mainDir, &pagesAmount);
  //treeTraversalInOrder(pageTree, printPage, NULL);  // For debug
  readGraph(pageTree, mainDir);
  //treeTraversalInOrder(pageTree, printOut, NULL);  // For debug


  //====================================================//
  //building main symbol table
  Tree* stopwords = buildStopWordsTree();
  treeTraversalInOrder(stopwords, printStopWord, NULL); // For debug
  //TODO: create terms symbol table, must think about implementation
  //====================================================//


  // Data processing=========//
  //PR math
  pageRanking(pagesAmount, pageTree);
  //treeTraversalInOrder(pageTree, printPage, NULL);

  // Consult reading=========//

  // Consult processing======//

  // Dealloc ================//
  treeFree(pageTree, freePage);
  treeFree(stopwords, NULL);
  free(mainDir);
  
  return 0;
}
