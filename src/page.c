#include <stdlib.h>
#include <stdio.h>

#include "../include/page.h"

struct page{
    double pageRank;
    char* pageName;
};

Page* createPage(double pageRank, char* pageName){
    Page* new = malloc(sizeof(Page));
    new->pageRank = pageRank;
    new->pageName = strdup(pageName);
    return new;
}

double getPageRank(Page* p){
    return p->pageRank;
}

char* getPageName(Page* p){
    return p->pageName;
}

void freePage(Page* p){
    free(p->pageName);
    free(p);
}




