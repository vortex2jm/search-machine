#include "../include/searchMachine.h"
#include "../include/page.h"
#include <stdio.h>
#include <stdlib.h>

// Protótipos================================//
void setPageRankCallback(void *node, void *PR);
void pageRanking(int pageAmount, pagesTree *pageTree);

// Implementação================================//
void pageRanking(int pageAmount, pagesTree *pageTree) {
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

void searchProcessor(termsTree* terms, stopWordTree* stopWords, char* mainDir){
  //TODO:IMPLEMENTAR
  //IDEIA DE ALGORITMO ENRICO E TAMELA:
  /**
   * PERCORRER ARQUIVO SEARCHES.TXT OBTENDO OS TERMOS A SEREM PESQUISADOS
   * VERIFICAR SE O TERMO ESTÁ NA ÁRVORE DE STOPWORDS, SE SIM, PARE, SE NÃO, CONTINUE
   * BUSCAR TERMO NA ARVORE DE TERMOS, INSERIR AS PAGINAS DELE NO VETOR
   *      --BOOL NA ESTRUTURA DA PAGINA PARA INDICAR SE JÁ FOI USADA (CONSTRUÇÃO DA INTERSEÇÃO)
   * SE ALGUM TERMO NÃO APARECER EM NENHUMA PÁGINA, NÃO HÁ NECESSIDADE DE CONTINUAR POIS A INTERSEÇÃO É NULA
   * COM TODOS OS TERMOS PERCORRIDOS, O RESULTADO É UM VETOR DESORDENADO DE PÁGINAS (JÁ É A INTERSEÇÃO)
   * ORDENAR VETOR PELO PR
   * PERCORRER VETOR IMPRIMINDO AS PÁGINAS E RETORNANDO O BOOLEANO PARA FALSO PARA USO DA PRÓXIMA PESQUISA
   * FIM DA PESQUISA
  */
}
