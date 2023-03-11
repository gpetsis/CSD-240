#include <stdio.h>
#include <stdlib.h>

#include "../main/pss.h"
#include "insert_info.h"



struct Info* insert_rec(struct Info* root, struct Info* new){

    struct Info* child;

    if(root == NULL){
        new->ip = NULL;
        return new;
    }

    if(new->itm < root->itm){
        child = insert_rec(root->ilc, new);
        root->ilc = child;
        child->ip = root;
    }else{
        child = insert_rec(root->irc, new);
        root->irc = child;
        child->ip = root;
    }
    return root;
}



int inorder(struct Info* root){
    int result = 1;
    
    if(root == NULL) return result;

    inorder(root->ilc);
    printf("%d%c", root->iId, ',');
    result = 0;
    inorder(root->irc);
    return result;
}



int handle_insert(int tm, int id, int* gp, int num){
    struct Info* current, *new, *parent;
    struct Info** currentinfo, **previnfo;
    int i, k, p, temp;

    if(id < 0 || id >= MG) return EXIT_FAILURE;


    k = 0;
    while(gp[k] != -1){
        if(gp[k] < 0 || gp[k] >= MG) return EXIT_FAILURE;
        k++;
    }

    k = 0;
    while(gp[k] != -1){
        current = groups[gp[k]]->gr;

        while(current != NULL){
            if(current->iId == id) return EXIT_FAILURE;

            if(current->iId < id){
                current = current->irc;
            }else{
                current = current->ilc;
            }
        }
        k++;
    }


    gp = bubbleSort(gp, num - 1);

    k = 0;
    while(gp[k] != -1){
        if(gp[k] == gp[k + 1]){
            k++;
            continue;
        }

        currentinfo = &groups[gp[k]]->gr;
        previnfo = &groups[gp[k]]->gr;


        new = (struct Info*)malloc(sizeof(struct Info));
        if(new == NULL){
            return EXIT_FAILURE;
        }

        new->iId = id;
        new->itm = tm;
        new->ilc = NULL;
        new->irc = NULL;

        for(i = 0; i < MG; i++){
            new->igp[i] = 0;
            p = 0;
            while(gp[p] != -1){
                if(gp[p] == i){
                    new->igp[i] = 1;
                }
                p++;
            }
        }

        if(*currentinfo == NULL){
            new->ip = NULL;
            *currentinfo = new;
            groups[gp[k]]->gr = new;
        }else{
            groups[gp[k]]->gr = insert_rec(groups[gp[k]]->gr, new);            
        }
        k++;
    }
    return EXIT_SUCCESS;
}



int* bubbleSort(int* array, int n){
    int i, j, temp;
    for (i = 0; i < n - 1; i++){
        for (j = 0; j < n - i - 1; j++){
            if (array[j] > array[j + 1]){
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
    return array;
}



void Print_insert(int* gp, int num){
    int k = 0, i;

    gp = bubbleSort(gp, num);

    for(i = 0; i < num; i++){
    printf("    GROUPID=<%d>, INFOLIST=<", groups[gp[k]]->gId);
        inorder(groups[gp[k]]->gr);
        printf("%c>\n", groups[gp[k]] != NULL ? 8 : '\0');
        k++;
    }

}