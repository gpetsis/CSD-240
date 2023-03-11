#include <stdio.h>
#include <stdlib.h>

#include "../main/pss.h"
#include "delete.h"
#include "sub_reg.h"



int handle_delete(int id){
    int i, j;
    struct SubInfo* current, *prev;
    struct Subscription* currentsub, *prevsub;
    struct TreeInfo* temp1, *temp2;


    current = findSub(id);
    if(current == NULL) return EXIT_FAILURE;

    for(i = 0; i < m; i++){
        current = subinfo[h(i)];
        if(current != NULL && current->sId == id){
            subinfo[h(i)] = current->snext;
            free(current);
            break;
        }

        while(current != NULL && current->sId != id){
            prev = current;
            current = current->snext;
        }

        if(current == NULL) continue;

        prev->snext = current->snext;
        free(current);
    }


    for(i = 0; i < MG; i++){
        currentsub = groups[i]->gsub;
        if(currentsub != NULL && currentsub->sId == id){
            groups[i]->gsub = currentsub->snext;
            free(currentsub);
            continue;
        }

        while(currentsub != NULL && currentsub->sId != id){
            prevsub = currentsub;
            currentsub = currentsub->snext;
        }

        if(currentsub == NULL){
            continue;
        }else{
            prevsub->snext = currentsub->snext;
            free(currentsub);
            continue;
        }
    }
}



void Print_delete(){
    int i;
    int array[MG];

    for(i = 0; i < MG; i++){
        array[i] = i;
    }
    Print_sub_reg(array, 64);
}