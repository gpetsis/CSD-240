#include <stdio.h>
#include <stdlib.h>

#include "../main/pss.h"
#include "consume.h"



struct TreeInfo* pointToRightest(struct TreeInfo* root){
    struct TreeInfo* current = root;

    while(current->tlc != NULL) current = current->tlc;

    while(current->next != NULL) current = current->next;
    return current;
}



int handle_consume(int id){
    struct SubInfo* current;
    int i;

    current = findSub(id);

    if(current == NULL) return EXIT_FAILURE;

    /* Subscriber not found */
    if(current->snext == NULL && current->sId != id) return EXIT_FAILURE;
    /*
    else if(current->snext == NULL && current->sId == id) current = current->snext;
    */


    for(i = 0; i < MG; i++){
        if(current->tgp[i] == (struct TreeInfo*) 1) continue;
        /* No info inserted in this group */
        if(current->sgp[i] == NULL && current->tgp[i] == NULL) continue;
        else{
            current->sgp[i] = pointToRightest(current->tgp[i]);
        }
        /*
        else if(current->sgp[i] == NULL && current->tgp[i] != NULL){
            current->sgp[i] = pointToRightest(current->tgp[i]);
        }
        */
    }
    return EXIT_SUCCESS;
}



void consume_print_leaves(struct TreeInfo* root, int id, int gid){
    int empty = 0;
    struct TreeInfo* current = root;
    struct SubInfo* currentsub = findSub(id);


    if(root == NULL) return;

    while(current->tlc != NULL) current = current->tlc;

    printf("    GROUPID=<%d>, TREELIST=<", gid);

    while(current != NULL){
        empty = 1;
        printf("%d,", current->tId);
        current = current->next;
    }
    printf("%c> NEWSGP=<%d>\n", empty == 1 ? 8 : 0, currentsub->sgp[gid]->tId);
}



void Print_consume(int id){
    int i;
    struct SubInfo* current;

    current = findSub(id);

    for(i = 0; i < MG; i++){
        if(current->tgp[i] == (struct TreeInfo*) 1) continue;

        if(old[i] == NULL){
            consume_print_leaves(current->tgp[i], id, groups[i]->gId);
        }else{
            consume_print_leaves(old[i], id, groups[i]->gId);
        }
    }
}