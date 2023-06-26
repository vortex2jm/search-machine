#include "../include/util.h"
#include "../include/redBlackTree.h"
#include "../include/page.h"
#include <stdio.h>
#include <stdlib.h>

void setPageRankCallback(void* node, void* PR){
  Tree* castTree = node;
  Page* castPage = treeGetValue(castTree);
  double* PRDouble = PR;
  setPageRank(castPage,*PRDouble);
}

//============================//
Tree *readPages(char *mainDir, int *pgCount){  
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
    tree = treeInsert(tree, line, pg, pageComparatorByName);
    pagesCounting++;
  }

  *pgCount = pagesCounting;
  return tree;
}

//========================================//
void readGraph(Tree * root, char * mainDir){
  // File reading
  char fileName[100];
  sprintf(fileName,"%s/%s", mainDir, GRAPH_FILE);
  FILE * graphFile = fopen(fileName, "r");

  // Processing======//
  size_t size = 0;
  int tokCounter=0;
  char *line = NULL, *token = NULL, *currentKey=NULL;
  Page * currentPage = NULL, *pageDest = NULL;
  Tree *currentNode = NULL, *outPages = NULL, *destInPages=NULL;

  while(getline(&line, &size, graphFile) != -1){
    // printf("%s", line);
    token = strtok(line, " \n");
    tokCounter=0;
    while(token){
      // printf("%s\n", token);
      if(!tokCounter){
        // Pegando o nó da árvore que contém a página com o primeiro nome da linha
        currentNode = treeSearch(root, token);
        currentPage = treeGetValue(currentNode);
        outPages = getPagesOut(currentPage);
      }
      else if(tokCounter == 1){
        // Settando a quantidade de nós que saem dessa página
        setPagesOutSize(currentPage, atoi(token));
      }
      else{
        // inserindo páginas que saem da página atual
        pageDest = treeGetValue(treeSearch(root, token)); //Página que sai da atual
        outPages = treeInsert(outPages, token, pageDest, pageComparatorByName); // Árvore de páginas que saem da atual
        setPagesInSize(pageDest); //Somando +1 nas páginas que saem da página que está saindo da atual
        destInPages = getPagesIn(pageDest); //Atualizando a árvore das páginas que saem da página que está saindo da atual
        destInPages = treeInsert(destInPages, getPageName(currentPage), currentPage, pageComparatorByName);
        setPagesIn(pageDest, destInPages);
      }
      token = strtok(NULL, " \n");
      tokCounter++;
    }
    setPagesOut(currentPage, outPages);
  } 
  free(line);
}

//================//
void pageRanking(int pageAmount, Tree* pageTree) {
  // TODO
  //Inicio de valor inicial  
  double firstPR = 1.0/(double)pageAmount;
  treeTraversalInOrder(pageTree,setPageRankCallback, &firstPR);

  double variation = 0.0;

  while(variation >= ALPHA){
    
  }
   
}

//================//
void indexer(){
  // TODO
}

//================//
void consult(){
  // TODO
}
