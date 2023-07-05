#include "../include/util.h"
#include "../include/page.h"
#include "../include/redBlackTree.h"
#include "../include/stopWordsTree.h"
#include "../include/termsTree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Protótipos================================//
stopWordTree *buildStopWordsTree(char *mainDir);
void linkPages(pagesTree *root, char *mainDir);
pagesTree *buildPagesTree(char *mainDir, int *pgCount);
termsTree *buildTermsTree(pagesTree *pages, stopWordTree *stopwords,
                          char *mainDir);
void printOut(void *v, void *argument);

// Implementação=============================//
//===========================================//
pagesTree *buildPagesTree(char *mainDir, int *pgCount) {
  char fileName[100] = "";
  sprintf(fileName, "%s/%s", mainDir, PAGES_FILE);
  FILE *pagesFile = fopen(fileName, "r");

  Tree *tree = NULL;
  Page *pg = NULL;

  char line[100];
  int pagesCounting = 0;
  while (!feof(pagesFile)) {
    fscanf(pagesFile, "%[^\n]\n", line);
    pg = createPage(line);
    tree = treeInsert(tree, line, pg, pageComparatorByName);
    pagesCounting++;
  }
  *pgCount = pagesCounting;
  fclose(pagesFile);
  return tree;
}

//========================================//
void linkPages(pagesTree *root, char *mainDir) {
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
        // Pegando o nó da árvore que contém a página com o primeiro nome da
        // linha
        currentPage = treeSearch(root, token);
        // currentPage = treeGetValue(currentNode);
        outPages = getPagesOut(currentPage);
      } else if (tokCounter == 1) {
        // Settando a quantidade de nós que saem dessa página
        setPagesOutSize(currentPage, atoi(token));
      } else {
        // inserindo páginas que saem da página atual
        pageDest = treeSearch(root, token); // Página que sai da atual
        outPages = treeInsert(
            outPages, token, pageDest,
            pageComparatorByName); // Árvore de páginas que saem da atual
        setPagesInSize(pageDest); // Somando +1 nas páginas que saem da página q
                                  // e está saindo da atual
        destInPages =
            getPagesIn(pageDest); // Atualizando a árvore das páginas que saem d
                                  //  página que está saindo da atual
        destInPages = treeInsert(destInPages, getPageName(currentPage),
                                 currentPage, pageComparatorByName);
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

// builds symbol table with stopwords.txt
// returns the root to the table
//=================================//
stopWordTree *buildStopWordsTree(char *mainDir) {
  char fileName[100];
  sprintf(fileName, "%s/%s", mainDir, STOP_WORDS_FILE);
  FILE *stopWordsFile = fopen(fileName, "r");
  char *currentWord = NULL;
  stopWordTree *root = NULL;
  size_t size = 0;
  bool wordIsthere = true;

  while (getline(&currentWord, &size, stopWordsFile) != -1) {
    currentWord = strtok(currentWord, " \n");
    // printf("%s\n", currentWord); //for debug
    root = treeInsert(root, currentWord, &wordIsthere, stopWordsCompare);
  }
  free(currentWord);
  fclose(stopWordsFile);

  return root;
}

//==============================================================//
termsTree *buildTermsTree(pagesTree *pages, stopWordTree *stopwords,
                          char *mainDir) {
  char fileName[100] = "";
  sprintf(fileName, "%s/%s", mainDir, PAGES_FILE);
  FILE *indexFile = fopen(fileName, "r");
  char *currentFile = NULL;
  size_t size = 0;
  termsTree *terms = NULL;
  Page *currentPage = NULL;
  Tree *currentTerm;
  Tree *currentPageTree;

  // percorre o conjunto de arquivos
  while (getline(&currentFile, &size, indexFile) != -1) {
    currentFile = strtok(currentFile, " \n");
    char pageDir[100] = "";
    sprintf(pageDir, "%s/%s/%s", mainDir, PAGES_FOLDER, currentFile);
    FILE *page = fopen(pageDir, "r");
    char *line = NULL;
    // percorre um arquivo
    while (getline(&line, &size, page) != -1) {
      char *word = strtok(line, " \n\t");
      while (word) {
        // se não estiver na árvore de stopWords,
        if (!treeSearch(stopwords, word)) {
          // o termo deve ser adicionado à arvore de termos
          // se o termo já estiver lá, deve-se apenas inserir a página em sua
          // árvore de páginas
          

          // Henrique Caetano Santos da Silva Pinto
          //REVISAR ESTE TRECHO=======================//
          currentTerm = treeSearch(terms, word);
          //============================================//
          

          // se o termo não está na árvore,
          if (currentTerm == NULL) {
            // ele deve ser adicionado
            terms = treeInsert(terms, word, NULL, termsTreeCompare);
          }
          currentPageTree = treeSearch(
              terms, word); // obtem a raiz da arvore de paginas
          currentPage =
              treeSearch(pages, currentFile); // obtem a pagina que deve ser inserida
          currentPageTree =
              treeInsert(currentPageTree, currentFile, currentPage,
                         pageComparatorByName); // insere
          // reinsere a palavra na árvore de termos, com a árvore de páginas
          // atualizada
          terms = treeInsert(terms, word, currentPageTree, termsTreeCompare);
        }
        // printf("%s", word); //for debug
        word = strtok(NULL, " \n\t");
      }
    }
    fclose(page);
    free(line);
  }
  free(currentFile);
  fclose(indexFile);
  return terms;
}

// Auxiliar=====================================//
void printOut(void *v, void *argument) {
  Page *p = treeGetValue((Tree *)v);
  printf("PAGINAS QUE SAEM DA PAGINA %s\n", getPageName(p));
  treeTraversalInOrder(getPagesOut(p), printPage, NULL);
  printf("PAGINAS QUE ENTRAM DA PAGINA %s\n", getPageName(p));
  treeTraversalInOrder(getPagesIn(p), printPage, NULL);
}


