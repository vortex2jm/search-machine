#include "../include/page.h"
#include "../include/util.h"
#include "../include/redBlackTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printOut(void * v){
  Page * p = treeGetValue((Tree*)v);
  printf("PAGINAS QUE SAEM DA PAGINA %s\n", getPageName(p));
  treeTraversalInOrder(getPagesOut(p), printPage);
}

int main(int argc, char *argv[]) {
  // Validation =============//
  if (argc < 2) {
    printf("You must insert main directory name!\n");
    return 1;
  }

  // Data reading============//
  int pagesAmount=0;
  char *mainDir = strdup(argv[1]);
  Tree * pageTree = readPages(mainDir, &pagesAmount);
  // treeTraversalInOrder(pageTree, printPage);  // For debug
  readGraph(pageTree, mainDir);
  // treeTraversalInOrder(pageTree, printOut);  // For debug

  // Data processing=========//

  // Consult reading=========//

  // Consult processing======//

  free(mainDir);

  return 0;
}
