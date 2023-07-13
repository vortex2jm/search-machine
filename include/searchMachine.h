#ifndef UTIL_H
#define UTIL_H

#include "page.h"
#include "ternarySearchTries.h"

#define PGR_LIMIT 0.000001

#define PAGES_FILE "index.txt"
#define GRAPH_FILE "graph.txt"
#define STOP_WORDS_FILE "stopwords.txt"
#define PAGES_FOLDER "pages"


/// @brief callback para liberação em árvore
/// @param value será um Page*
void termTreeFreePagesTree(void* value);


/// @brief Lê arquivo "graph.txt" e insere páginas que entram e saem de outra página
/// @param root inicio da árvore de paginas
/// @param mainDir diretório que contém "graph.txt"
void linkPages(PagesTree *root, char *mainDir);


/// @brief Lê arquivo "index.txt" e cria uma TST de páginas
/// @param mainDir diretório que contém "graph.txt"
/// @param pgCount informação da quantidade de páginas dentro da árvore
/// @return raiz da árvore
PagesTree *buildPagesTree(char *mainDir, int *pgCount);


/// @brief Lê arquivo "stopwords.txt" e cria a TST de stopwords
/// @param mainDir diretório que contém "graph.txt"
/// @return raiz da árvore
StopWordTree *buildStopWordsTree(char *mainDir);

// Cria árvore principal (de termos)

/// @brief Lê arquivos "index.txt" e pasta pages, construindo a árvore de termos
/// @param pages TST com todas as páginas
/// @param stopwords TST de stopwords
/// @param mainDir diretório que contém "graph.txt" 
/// @return árvore em que chave -> termo e valor -> raiz da TST de páginas em que o termo aparece
TermsTree *buildTermsTree(PagesTree *pages, StopWordTree *stopwords, char *mainDir);

/// @brief calcula o pageRanking de cada página
/// @param pageAmount quantidade de páginas
/// @param pageTree raiz da TST de páginas
void pageRanking(int pageAmount, PagesTree *pageTree);



/// @brief recebe termos a serem pesquisados e obtém as páginas relevantes, em ordem
/// @param terms TST de termos
/// @param stopWords TST de stopwords
/// @param pagesAmount quantidade de páginas
void searchProcessor(TermsTree *terms, StopWordTree *stopWords, int pagesAmount);

#endif // !UTIL_H