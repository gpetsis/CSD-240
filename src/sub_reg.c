#include <stdio.h>
#include <stdlib.h>

#include "../main/pss.h"
#include "sub_reg.h"
#include "insert_info.h"



int handle_sub_reg(int tm, int id, int* gp, int num){
    struct SubInfo* current, *new, *prev;
    struct Subscription* currentsub, *newsub;
    int x, i, k;

    if(id < 0 || id >= MG) return EXIT_FAILURE;

    x = h(id);

    current = subinfo[x];
    while(current != NULL){
        if(current->sId == id){
            return EXIT_FAILURE;
        }
        current = current->snext;
    }

    new = (struct SubInfo*)malloc(sizeof(struct SubInfo));

    if(new == NULL) return EXIT_FAILURE;

    new->sId = id;
    new->stm = tm;

    current = subinfo[x];
    if(current == NULL || current->sId > id){
        new->snext = subinfo[x];
        subinfo[x] = new;
    }else{
        while(current->snext != NULL && current->snext->sId < id){
            current = current->snext;
        }

        new->snext = current->snext;
        current->snext = new;
    }

    for(i = 0; i < MG; i++){
        new->tgp[i] = (struct TreeInfo*) 1;
        new->sgp[i] = NULL;
    }

    gp = bubbleSort(gp, num - 1);

    k = 0;
    while(gp[k] != -1){
        if(gp[k] == gp[k + 1]){
            k++;
            continue;
        }
        currentsub = groups[gp[k]]->gsub;
        newsub = (struct Subscription*)malloc(sizeof(struct Subscription));
        if(newsub == NULL){
            return EXIT_FAILURE;
        }
        newsub->sId = id;
        newsub->snext = NULL;
        if(currentsub != NULL){
            while(currentsub->snext != NULL){
                currentsub = currentsub->snext;
            }
            currentsub->snext = newsub;
        }else{
            newsub->snext = NULL;
            groups[gp[k]]->gsub = newsub;
        }

        new->tgp[gp[k]] = NULL;
        k++;
    }
    return EXIT_SUCCESS;
}



void Print_sub_reg(int* gp, int num){
    int i, k, isEmpty = 0;
    struct SubInfo* current;
    struct Subscription* currentsub;

    printf("    SUBSCRIBERLIST=<");
    for(i = 0; i < m; i++){
        current = subinfo[h(i)];
        while(current != NULL){
            isEmpty = 1;
            printf("%d,", current->sId);
            current = current->snext;
        }
    }
    printf("%c>\n", isEmpty == 1 ? 8 : 0);

    k = 0;
    gp = bubbleSort(gp, num - 1);
    for(i = 0; i < num - 1; i++){
        isEmpty = 0;
        if(gp[k] == gp[k + 1]){
            k++;
            continue;
        }
        currentsub = groups[gp[k]]->gsub;
        printf("    GROUPID = <%d>, SUBLIST = <", groups[gp[k]]->gId);
        while(currentsub != NULL){
            isEmpty = 1;
            printf("%d%c", currentsub->sId, ',');
            currentsub = currentsub->snext;
        }
        printf("%c>\n", isEmpty == 1 ? 8 : 0);
        k++;
    }
}