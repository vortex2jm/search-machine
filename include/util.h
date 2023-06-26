#ifndef UTIL_H
#define UTIL_H
#include "page.h"
#include "redBlackTree.h"
#include "stopWordsTree.h"
#include "termsTree.h"

#define PAGES_FILE "index.txt"
#define GRAPH_FILE "graph.txt"
#define PGR_LIMIT 0.000001

Tree *readPages(char *mainDir, int *pgCount);

void readGraph(Tree * root, char * mainDir);

void pageRanking(int pageAmount, Tree* pageTree);

stopWordTree* buildStopWordsTree();

termsTree* buildTermsTree(Tree* pages, stopWordTree* stopwords);


void indexer();
// void consult();

#endif // !UTIL_H
