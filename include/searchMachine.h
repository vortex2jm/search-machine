#ifndef SEARCH_MACHINE
#define SEARCH_MACHINE
#include "redBlackTree.h"

#define PGR_LIMIT 0.000001

// Calcula o page ranking das páginas que estão na árvore de páginas
void pageRanking(int pageAmount, pagesTree *pageTree);

//recebe termos a serem pesquisados e obtém as páginas relevantes, em ordem
void searchProcessor(termsTree* terms, stopWordTree* stopWords, char* mainDir);


#endif // !SEARCH_MACHINE
