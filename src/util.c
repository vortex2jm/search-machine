#include "../include/util.h"
#include "../include/page.h"
#include "../include/termsTree.h"
#include "../include/redBlackTree.h"
#include "../include/stopWordsTree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Protótipos================================//
stopWordTree *buildStopWordsTree();
void readGraph(Tree *root, char *mainDir);
Tree *readPages(char *mainDir, int *pgCount);
void setPageRankCallback(void *node, void *PR);
void pageRanking(int pageAmount, Tree *pageTree);
termsTree *buildTermsTree(Tree *pages, stopWordTree *stopwords);

// Implementação=============================//
//===========================================//
void setPageRankCallback(void *node, void *PR) {
  Tree *castTree = node;
  Page *castPage = treeGetValue(castTree);
  double *PRDouble = PR;
  setPageRank(castPage, *PRDouble);
  setLastPageRank(castPage, *PRDouble);
}

//===========================================//
Tree *readPages(char *mainDir, int *pgCount) {
  char fileName[100];
  sprintf(fileName, "%s/%s", mainDir, PAGES_FILE);
  FILE *pagesFile = fopen(fileName, "r");

  Tree *tree = NULL;
  Page *pg = NULL;

  char line[100];
  int pagesCounting = 0;
  while (!feof(pagesFile)) {
    fscanf(pagesFile, "%[^\n]\n", line);
    pg = createPage(line);
    tree = treeInsert(tree, line, pg, pageComparatorByName, KEY_COMPARE);
    pagesCounting++;
  }
  *pgCount = pagesCounting;
  fclose(pagesFile);
  return tree;
}

//========================================//
void readGraph(Tree *root, char *mainDir) {
  // File reading
  char fileName[100];
  sprintf(fileName, "%s/%s", mainDir, GRAPH_FILE);
  FILE *graphFile = fopen(fileName, "r");

  // Processing//
  size_t size = 0;
  int tokCounter = 0;
  char *line = NULL, *token = NULL, *currentKey = NULL;
  Page *currentPage = NULL, *pageDest = NULL;
  Tree *currentNode = NULL, *outPages = NULL, *destInPages = NULL;

  while (getline(&line, &size, graphFile) != -1) {
    token = strtok(line, " \n");
    tokCounter = 0;
    while (token) {
      if (!tokCounter) {
        // Pegando o nó da árvore que contém a página com o primeiro nome da linha
        currentNode = treeSearch(root, token);
        currentPage = treeGetValue(currentNode);
        outPages = getPagesOut(currentPage);
      } else if (tokCounter == 1) {
        // Settando a quantidade de nós que saem dessa página
        setPagesOutSize(currentPage, atoi(token));
      } else {
        // inserindo páginas que saem da página atual
        pageDest =
            treeGetValue(treeSearch(root, token)); // Página que sai da atual
        outPages =
            treeInsert(outPages, token, pageDest, pageComparatorByName,
                       KEY_COMPARE); // Árvore de páginas que saem da atual
        setPagesInSize(pageDest); // Somando +1 nas páginas que saem da página q
                                  // e está saindo da atual
        destInPages =
            getPagesIn(pageDest); // Atualizando a árvore das páginas que saem d
                                  //  página que está saindo da atual
        destInPages =
            treeInsert(destInPages, getPageName(currentPage), currentPage,
                       pageComparatorByName, KEY_COMPARE);
        setPagesIn(pageDest, destInPages);
      }
      token = strtok(NULL, " \n");
      tokCounter++;
    }
    setPagesOut(currentPage, outPages);
  }
  fclose(graphFile);
  free(line);
}

//===============================================//
void pageRanking(int pageAmount, Tree *pageTree) {
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

// builds symbol table with stopwords.txt
// returns the root to the table
//=================================//
stopWordTree *buildStopWordsTree() {
  FILE *stopWordsFile = fopen("./tests/stopwords.txt", "r");
  char *currentWord = NULL;
  size_t size = 0;
  stopWordTree *root = NULL;

  while (getline(&currentWord, &size, stopWordsFile) != -1) {
    currentWord = strtok(currentWord, " \n");
    // printf("%s\n", currentWord); //for debug
    root = stopWordTreeInsert(root, currentWord, KEY_COMPARE);
  }
  free(currentWord);
  fclose(stopWordsFile);

  return root;
}

//==============================================================//
termsTree *buildTermsTree(Tree *pages, stopWordTree *stopwords) {
  FILE *indexFile = fopen("./tests/index.txt", "r");
  char *currentFile = NULL;
  size_t size = 0;
  termsTree *terms = NULL;
  Page *currentPage = NULL;

  // percorre o conjunto de arquivos
  while (getline(&currentFile, &size, indexFile) != -1) {
    currentFile = strtok(currentFile, " \n");
    char *pageDir = strdup(currentFile);
    sprintf(pageDir, "./tests/pages/%s", currentFile);

    FILE *page = fopen(pageDir, "r");
    char *line = NULL;
    // percorre um arquivo
    while (getline(&line, &size, page) != -1) {
      char *word = strtok(line, " \n\t");
      // se a word não estiver na árvore de stopwords
      if (stopWordTreeSearch(stopwords, word) == NULL) {
        currentPage = treeGetValue(treeSearch(pages, currentFile));
        terms = termsTreeInsert(terms, word, currentPage, KEY_COMPARE);
      }
    }
    free(pageDir);
    fclose(page);
  }
  fclose(indexFile);
  return terms;
}

//=====================================//
void printOut(void * v,void * argument){
  Page * p = treeGetValue((Tree*)v);
  printf("PAGINAS QUE SAEM DA PAGINA %s\n", getPageName(p));
  treeTraversalInOrder(getPagesOut(p), printPage, NULL);
  printf("PAGINAS QUE ENTRAM DA PAGINA %s\n", getPageName(p));
  treeTraversalInOrder(getPagesIn(p), printPage, NULL);
}

//=============//
void consult() {
  // TODO
}
