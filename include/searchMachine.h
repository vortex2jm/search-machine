#ifndef UTIL_H
#define UTIL_H
#include "page.h"
#include "redBlackTree.h"

#define PGR_LIMIT 0.000001

#define PAGES_FILE "index.txt"
#define GRAPH_FILE "graph.txt"
#define STOP_WORDS_FILE "stopwords.txt"
#define PAGES_FOLDER "pages"

// callback
void termTreeFreePagesTree(void* value); 

// Lê o arquivo "graph.txt" e insere as páginas
// que entram e saem de outra página
void linkPages(PagesTree *root, char *mainDir);

// Cria árvore de stop words
StopWordTree *buildStopWordsTree(char *mainDir);

// Calcula o page ranking das páginas que estão na árvore de páginas
void pageRanking(int pageAmount, PagesTree *pageTree);

// Lê as páginas do arquivo "index.txt" e cria uma
// árvore rubro-negra de páginas
PagesTree *buildPagesTree(char *mainDir, int *pgCount);

// recebe termos a serem pesquisados e obtém as páginas relevantes, em ordem
void searchProcessor(TermsTree *terms, StopWordTree *stopWords, int pagesAmount);

// Cria árvore principal (de termos)
TermsTree *buildTermsTree(PagesTree *pages, StopWordTree *stopwords, char *mainDir);

#endif // !UTIL_H
