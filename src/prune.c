#include <stdio.h>
#include <stdlib.h>

#include "../main/pss.h"
#include "prune.h"
#include "sub_reg.h"
#include "insert_info.h"



struct TreeInfo* newTree(int id, int tm){
    struct TreeInfo* new = (struct TreeInfo*)malloc(sizeof(struct TreeInfo));
    new->tId = id;
    new->ttm = tm;
    new->tlc = NULL;
    new->trc = NULL;
    return new;
}



struct Info* minValueNode(struct Info* node){
    struct Info* current = node;
    while (current && current->ilc != NULL)
        current = current->ilc;
    return current;
}



struct Info* delete_Node(struct Info* root, int tm){
    int i;
    if(root == NULL) return root;

    if(tm < root->itm) root->ilc = delete_Node(root->ilc, tm);
    else if(tm > root->itm) root->irc = delete_Node(root->irc, tm);
    else{
        if(root->ilc == NULL){
            struct Info* temp = root->irc;
            free(root);
            return temp;
        }else if(root->irc == NULL){
            struct Info* temp = root->ilc;
            free(root);
            return temp;
        }

        struct Info* temp = minValueNode(root->irc);

        root->itm = temp->itm;
        root->iId = temp->iId;
        for(i = 0; i < MG; i++){
            root->igp[i] = temp->igp[i];
        }

        root->irc = delete_Node(root->irc, tm);
    }

}



struct Info* delete_multiples(struct Info* root){
    struct Info* currentl, *currentr;
    
    if(root == NULL) return root;

    root->ilc = delete_multiples(root->ilc);
    root->irc = delete_multiples(root->irc);

    if(root->ilc != NULL){
        if(root->iId == root->ilc->iId){
            root = delete_Node(root, root->ilc->itm);
        }
    }
    if(root->irc != NULL){
        if(root->iId == root->irc->iId){
            root = delete_Node(root, root->irc->itm);
        }
    }

    return root;
}



struct TreeInfo* insert_leaf_oriented(struct TreeInfo* root, int id, int tm){
    struct TreeInfo* newl, *newr, *current;

    newl = (struct TreeInfo*)malloc(sizeof(struct TreeInfo));

    if(root == NULL){
        newl = newTree(id, tm);
        newl->tp = NULL;
        newl->next = NULL;
        newl->prev = NULL;
        root = newl;
        return root;
    }else{
        newr = (struct TreeInfo*)malloc(sizeof(struct TreeInfo));
        current = root;
        while(current->tlc != NULL && current->trc != NULL){
            if(current->tId < id){
                current = current->trc;
            }else{
                current = current->tlc;
            }
        }
        if(current->tId < id){
            newr = newTree(id, tm);
            newr->tp = current;
            current->trc = newr;
            newl = newTree(current->tId, current->ttm);
            newl->tp = current;
            current->tlc = newl;
        }else{
            newl = newTree(id, tm);
            newl->tp = current;
            current->tlc = newl;
            newr = newTree(current->tId, current->ttm);
            newr->tp = current;
            current->trc = newr;
            current->tId = id;
            current->ttm = tm;
        }
        newr->prev = newl;
        newr->next = current->next;
        newl->prev = current->prev;
        newl->next = newr;
        if(current->prev != NULL){
            current->prev->next = newl;
        }else{
            current->prev = NULL;
        }
        if(current->next != NULL){
            current->next->prev = newr;
        }else{
            current->next = NULL;
        }
        current->next = NULL;
        current->prev = NULL;
        return root;
    }
}



struct Info* delete_Info(struct Info* root, int tm, int gid){
    int i, j;
    struct Info* temp;
    struct SubInfo* current;
    
    if(root == NULL) return NULL;

    root->irc = delete_Info(root->irc, tm, gid);
    root->ilc = delete_Info(root->ilc, tm, gid);
    
    if(root->itm <= tm){
        for(j = 0; j < m; j++){
            current = subinfo[j];
            while(current != NULL){
                if(current->tgp[gid] != (struct TreeInfo*) 1){
                    current->tgp[gid] = insert_leaf_oriented(current->tgp[gid], root->iId, root->itm);
                }
                current = current->snext;
            }
        }

        if(root->ilc == NULL){
            struct Info* temp = root->irc;
            free(root);
            return temp;
        }else if(root->irc == NULL){
            struct Info* temp = root->ilc;
            free(root);
            return temp;
        }

        if(root->ilc->ilc == NULL && root->ilc->irc == NULL && root->ilc->itm <= tm){
            struct Info* temp = root->irc;
            free(temp);
            return root;
        }else if(root->irc->ilc == NULL && root->irc->irc == NULL && root->irc->itm <= tm){
            struct Info* temp = root->ilc;
            free(temp);
            return root;
        }

        temp = minValueNode(root->irc);


        root->itm = temp->itm;
        root->iId = temp->iId;
        for(i = 0; i < MG; i++){
            root->igp[i] = temp->igp[i];
        }

        root->irc = delete_Node(root->irc, temp->itm);
    }
    return root;
}



int handle_prune(int tm){
    int i;
    struct Info* currentinfo, *temp;
    struct TreeInfo* currenttree;

    for(i = 0; i < MG; i++){
        currentinfo = groups[i]->gr;
        temp = delete_Info(currentinfo, tm, i);
        temp = delete_multiples(temp);
        groups[i]->gr = temp;
    }
    return EXIT_SUCCESS;
}



int inorderT(struct TreeInfo* root){
    int result = 1;

    if(root == NULL) return;

    inorderT(root->tlc);
    printf("%d,", root->tId);
    result = 0;
    inorderT(root->trc);
    return result;
}



int printLeafs(struct TreeInfo* root, int gid){
    int result = 1;
    struct TreeInfo* current = root;

    if(current == NULL) return 1;

    while(current->tlc != NULL) current = current->tlc;

    while(current != NULL){
        result = 0;
        printf("%d(<%d>),", current->tId, gid);
        current = current->next;
    }
    return result;
}



void printInfoSublist(){
    int i, exists;
    struct Info* currentinfo;
    struct Subscription* currentsubscriber;

    for(i = 0; i < MG; i++){
        noGroups++;
        printf("    GROUPID=<%d>, INFOLIST=<", groups[i]->gId);
        currentinfo = groups[i]->gr;
        exists = inorder(currentinfo);
        printf("%c>, SUBLIST=<", exists == 1 ? 0 : 8);
        currentsubscriber = groups[i]->gsub;
        exists = 1;
        while(currentsubscriber != NULL){
            exists = 0;
            printf("%d,", currentsubscriber->sId);
            currentsubscriber = currentsubscriber->snext;
        }
        printf("%c>\n", exists == 1 ? 0 : 8);
    }
}



void printSubTreelist(){
    int i, j, exists;
    struct SubInfo* currentsub;

    for(i = 0; i < m; i++){
        currentsub = subinfo[h(i)];
        while(currentsub != NULL){
            noSubs++;
            printf("    SUBSCRIBERID=<%d>, GROUPLIST=<\n", currentsub->sId);
            for(j = 0; j < MG; j++){
                if(currentsub->tgp[j] == (struct TreeInfo*) 1) continue;
                printf("        <%d>, TREELIST=<", groups[j]->gId);
                exists = printLeafs(currentsub->tgp[j], groups[j]->gId);
                printf("%c>\n", exists == 1 ? 0 : 8);
            }
            currentsub = currentsub->snext;
        }
    }
}



void Print_prune(){
    int i, j, exists;
    struct Info* currentinfo;
    struct SubInfo* currentsub;
    struct Subscription* currentsubscriber;

    printInfoSublist();

    printSubTreelist();
}