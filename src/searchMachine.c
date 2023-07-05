#include "../include/searchMachine.h"
#include "../include/page.h"
#include "../include/redBlackTree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Protótipos================================//
int keyComparator(void* c1, void* c2);
void termTreeFreePagesTree(void* value);
void setPageRankCallback(void *node, void *PR);
void linkPages(PagesTree *root, char *mainDir);
StopWordTree *buildStopWordsTree(char *mainDir);
void pageRanking(int pageAmount, PagesTree *pageTree);
PagesTree *buildPagesTree(char *mainDir, int *pgCount);
void searchProcessor(TermsTree *terms, StopWordTree *stopWords, int pagesAmount);
TermsTree *buildTermsTree(PagesTree *pages, StopWordTree *stopwords, char *mainDir);

// Implementação=============================//
PagesTree *buildPagesTree(char *mainDir, int *pgCount) {
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
void linkPages(PagesTree *root, char *mainDir) {
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

//=================================//
StopWordTree *buildStopWordsTree(char *mainDir) {
  char fileName[100];
  sprintf(fileName, "%s/%s", mainDir, STOP_WORDS_FILE);
  FILE *stopWordsFile = fopen(fileName, "r");
  char *currentWord = NULL;
  StopWordTree *root = NULL;
  size_t size = 0;
  bool wordIsthere = true;

  while (getline(&currentWord, &size, stopWordsFile) != -1) {
    currentWord = strtok(currentWord, " \n");
    // printf("%s\n", currentWord); //for debug
    root = treeInsert(root, currentWord, &wordIsthere, keyComparator);
  }
  free(currentWord);
  fclose(stopWordsFile);

  return root;
}

//==============================================================//
TermsTree *buildTermsTree(PagesTree *pages, StopWordTree *stopwords,
                          char *mainDir) {
  char fileName[100] = "";
  sprintf(fileName, "%s/%s", mainDir, PAGES_FILE);
  FILE *indexFile = fopen(fileName, "r");
  char *currentFile = NULL;
  size_t size = 0;
  TermsTree *terms = NULL;
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
            terms = treeInsert(terms, word, NULL, keyComparator);
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
          terms = treeInsert(terms, word, currentPageTree, keyComparator);
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

//====================================//
void termTreeFreePagesTree(void* value){
    treeFree(value, NULL);
}

//==================================//
int keyComparator(void* c1, void* c2){
    return strcasecmp((char*)c1, (char*)c2);
}

void pageRanking(int pageAmount, PagesTree *pageTree) {
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

//============================================//
void setPageRankCallback(void *node, void *PR) {
  Tree *castTree = node;
  Page *castPage = treeGetValue(castTree);
  double *PRDouble = PR;
  setPageRank(castPage, *PRDouble);
  setLastPageRank(castPage, *PRDouble);
}

//=========================================================//
void searchProcessor(TermsTree *terms, StopWordTree *stopWords, int pagesAmount) {
  //===================//
  int termsAmount = 0;  // Quantidade de termos
  size_t bufferSize = 0;  //auxiliar
  PagesTree *termPages = NULL;  // Árvore de páginas que contém o termo
  char *buffer = NULL, *search=NULL, * token = NULL;

  //Vetor de páginas que contém os termos===================================//
  // Este vetor foi alocado com a quantidade de páginas que tem na árvore
  // de páginas, mas não necessariamente todas elas estarão lá dentro
  Page **intersectionPages = calloc(pagesAmount, sizeof(Page *));
  int intersectionIndex = 0;  // próximo índice livre do vetor

  //Argumentos da callback==================================================//
  void ** pagesIntersectionArguments = malloc(sizeof(void*)*2);
  pagesIntersectionArguments[0] = intersectionPages;  //vetor
  pagesIntersectionArguments[1] = &intersectionIndex; //próximo índice livre

  //========================================================//
  while (getline(&buffer, &bufferSize, stdin) != -1) {
    // Copiando o conteudo do buffer para a variavel search pois o strtok modifica a variável buffer
    search = strdup(buffer);

    // Separando as strings da consulta
    token = strtok(buffer, " \n");
    while(token){
      if (!treeSearch(stopWords, token)) {
        // Garantindo que as palavras da cconsulta estarão na árvore, podemos retirar esta verificação
        if((termPages = treeSearch(terms, token))){
          // Atravessando a árvore de páginas que contém os termos e adicionando-as no vetor a ser ordenado
          // caso ainda não esteja lá e incrementando o contador de intersecção
          treeTraversalInOrder(termPages, intersectionProcessor, pagesIntersectionArguments);
        }
      }
      token = strtok(NULL, " \n");
      termsAmount++;  //Adicionando o contador de termos
    }
    
    // Ordenando o vetor de páginas
    qsort(intersectionPages, intersectionIndex, sizeof(Page*), comparatorPagesVector);
    printConsult(search, intersectionPages, intersectionIndex, termsAmount);
    intersectionIndex = 0;
    termsAmount = 0;
  }

  free(buffer);
  free(search);
  free(intersectionPages);
  free(pagesIntersectionArguments);
}
