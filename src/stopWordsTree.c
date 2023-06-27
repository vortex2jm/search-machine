#include <stdio.h>
#include <strings.h>
#include "../include/stopWordsTree.h" 



int stopWordsCompare(void* c1, void* c2){
    return strcasecmp((char*) c1,(char*) c2);
}

void printStopWord(void* node, void* arg){
    char* word = (char*) treeGetKey((stopWordTree*) node);
    printf("%s\n", word);
}

