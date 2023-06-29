#include <strings.h>
#include "../include/termsTree.h"

int termsTreeCompare(void* c1, void* c2){
    return strcasecmp((char*)c1, (char*)c2);
}

void termTreePrintNode(void* value, void* arg){
    printf("WORD:%s\n", treeGetKey((Tree*) value));
    treeTraversalInOrder(treeGetValue(value), printPage, NULL);
}

void termTreeFreePagesTree(void* value){
    treeFree(value, NULL);
}