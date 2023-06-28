#ifndef UTIL_H
#define UTIL_H
#include "page.h"
#include "redBlackTree.h"
// #include "stopWordsTree.h"
// #include "termsTree.h"

#define PAGES_FILE "index.txt"
#define GRAPH_FILE "graph.txt"
#define STOP_WORDS_FILE "stopwords.txt"

// Função auxiliar
void printOut(void *v, void *argument);

// Lê o arquivo "graph.txt" e insere as páginas
// que entram e saem de outra página
void linkPages(pagesTree *root, char *mainDir);

// Lê as páginas do arquivo "index.txt" e cria uma
// árvore rubro-negra de páginas
pagesTree *buildPagesTree(char *mainDir, int *pgCount);

// Cria árvore de stop words
stopWordTree *buildStopWordsTree(char *mainDir);

// Cria árvore principal (de termos)
termsTree *buildTermsTree(pagesTree *pages, stopWordTree *stopwords,
                          char *mainDir);

#endif // !UTIL_H
