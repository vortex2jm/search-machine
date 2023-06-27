#include "../include/stopWordsTree.h" 
#include <strings.h>
#include <stdio.h>

static int stopWordsCompare(void* c1, void* c2){
    return strcasecmp((char*) c1,(char*) c2);
}

static void printStopWord(void* node, void* arg){
    char* word = stopWordGetValue((stopWordTree*) node);
    printf("%s\n", word);
}

stopWordTree* stopWordTreeInsert(stopWordTree* node, char* key, int compareMode){
   return (stopWordTree *) treeInsert((Tree*) node, key, key, stopWordsCompare, compareMode);
}

stopWordTree* stopWordTreeSearch(stopWordTree* root, char* key){
    return treeSearch(root, key);
}

char* stopWordTreeGetValue(stopWordTree* node){
    return (char*) treeGetValue(node);
}

void stopWordtreeTraversalInOrder(stopWordTree * node){
  treeTraversalInOrder((Tree*) node, printStopWord, NULL);
}

char* stopWordGetValue(stopWordTree * node){
    return (char*) treeGetKey(node);
}

void stopWordTreeFree(stopWordTree* root){
    treeFree(root);
}
