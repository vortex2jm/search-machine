#include <strings.h>
#include "../include/termsTree.h"

static int termsTreeCompare(void* c1, void* c2){
    return strcasecmp((char*)c1, (char*)c2);
}

termsTree* termsTreeInsert(termsTree* node, char* key, Page* p, int compareMode){
    termsTree* root = treeInsert(node, key, NULL, termsTreeCompare, compareMode);//insere o termo atual com valor nulo
    termsTree* aux = treeSearch(aux, key); //encontramos o nó do termo atual
    treeInsert(treeGetValue(aux), getPageName(p), p, pageComparatorByName, compareMode); //insere a pagina na arvore de paginas

    return root;
}

termsTree* termsTreeSearch(Tree* root, char* key){
    return treeSearch(root, key);
}

void* termsTreeGetValue(termsTree* node){
    return treeGetValue(node);
}

// void termsTreeFree(termsTree* root){
//     treeFree(root);
// }
