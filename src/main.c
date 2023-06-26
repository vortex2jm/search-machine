#include "../include/page.h"
#include "../include/util.h"
#include "../include/redBlackTree.h"
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
  char *mainDir = strdup(argv[1]);
  Tree * pageTree = readPages(mainDir);
  treeTraversalInOrder(pageTree, printPage);  // For debug

  // Data processing=========//

  // Consult reading=========//

  // Consult processing======//

  free(mainDir);

  return 0;
}
