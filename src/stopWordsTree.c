#include "../include/stopWordsTree.h" 
#include <strings.h>

static int stopWordsCompare(void* c1, void* c2){
    return strcasecmp((char*) c1,(char*) c2);
}

stopWordTree* stopWordTreeInsert(stopWordTree* node, char* key){
   return treeInsert(node, key, key, stopWordsCompare);
}

stopWordTree* stopWordTreeSearch(stopWordTree* root, char* key){
    return treeSearch(root, key);
}

char* stopWordTreeGetValue(stopWordTree* node){
    return (char*) treeGetValue(node);
}

void stopWordTreeFree(stopWordTree* root){
    treeFree(root);
}
