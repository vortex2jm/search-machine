#include "../include/util.h"
#include "../include/redBlackTree.h"
#include "../include/page.h"
#include <stdio.h>
#include <stdlib.h>

//============================//
Tree *readPages(char * mainDir){  
  char fileName[100];
  sprintf(fileName,"%s/%s", mainDir, PAGES_FILE);
  FILE * pagesFile = fopen(fileName, "r");

  Tree * tree = NULL;
  Page * pg = NULL;

  char line[100];
  int pagesCounting=0;
  while(!feof(pagesFile)){
    fscanf(pagesFile,"%[^\n]\n", line);
    pg = createPage(line);
    tree = treeInsert(tree, line, pg, pageComparator);
  }
  return tree;
}

//================//
void pageRanking() {
  // TODO
}

//================//
void indexer(){
  // TODO
}

//================//
void consult(){
  // TODO
}
