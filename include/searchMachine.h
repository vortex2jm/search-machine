#ifndef SEARCH_MACHINE
#define SEARCH_MACHINE
#include "ternarySearchTries.h"

#define PGR_LIMIT 0.000001

// Calcula o page ranking das páginas que estão na árvore de páginas
void pageRanking(int pageAmount, pagesTree *pageTree);

// recebe termos a serem pesquisados e obtém as páginas relevantes, em ordem
void searchProcessor(termsTree *terms, stopWordTree *stopWords,
                     int pagesAmount);

#endif // !SEARCH_MACHINE
