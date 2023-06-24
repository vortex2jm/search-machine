#include "../include/page.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

  // Validation =============//
  if (argc < 2) {
    printf("You must insert main folder name!\n");
    return 1;
  }

  // Data reading============//
  char *mainDir = strdup(argv[1]);

  // Data processing=========//

  // Consult reading=========//

  // Consult processing======//

  free(mainDir);

  return 0;
}
