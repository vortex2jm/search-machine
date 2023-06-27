#ifndef UTIL_H
#define UTIL_H
#include "page.h"
#include "termsTree.h"
#include "redBlackTree.h"
#include "stopWordsTree.h"

#define PGR_LIMIT 0.000001
#define PAGES_FILE "index.txt"
#define GRAPH_FILE "graph.txt"

stopWordTree *buildStopWordsTree();

//Função auxiliar
void printOut(void * v,void * argument);

// Lê o arquivo "graph.txt" e insere as páginas
// que entram e saem de outra página
void readGraph(Tree *root, char *mainDir);

// Lê as páginas do arquivo "index.txt" e cria uma
// árvore rubro-negra de páginas
Tree *readPages(char *mainDir, int *pgCount);

// Calcula o page ranking das páginas que estão
// na árvore rubro-negra ed páginas
void pageRanking(int pageAmount, Tree *pageTree);

// 
termsTree *buildTermsTree(Tree *pages, stopWordTree *stopwords);

// void indexer();
// void consult();

#endif // !UTIL_H
