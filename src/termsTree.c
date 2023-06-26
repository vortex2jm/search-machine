#include "../include/termsTree.h"
#include <strings.h>

static int termsTreeCompare(void* c1, void* c2){
    return strcasecmp((char*)c1, (char*)c2);
}

termsTree* termsTreeInsert(termsTree* node, char* key, Tree* value, Page* p){
    //return treeInsert(node, key, value, termsTreeCompare);
    termsTree* root = (node, key, value, termsTreeCompare);//insere o termo atual
    termsTree* aux = treeSearch(aux, key); //encontramos o nó do termo atual
    treeInsert(treeGetValue(aux), getPageName(p), p, pageComparatorByName);

    return root;
}

termsTree* termsTreeSearch(Tree* root, char* key){
    return treeSearch(root, key);
}

void* termsTreeGetValue(termsTree* node){
    return treeGetValue(node);
}

void termsTreeFree(termsTree* root){
    treeFree(root);
}