/***************************************************************
 *
 * file: pss.h
 *
 * @Author  Nikolaos Vasilikopoulos (nvasilik@csd.uoc.gr), John Petropoulos (johnpetr@csd.uoc.gr)
 * @Version 30-11-2022
 *
 * @e-mail       hy240-list@csd.uoc.gr
 *
 * @brief   Implementation of the "pss.h" header file for the Public Subscribe System,
 * function definitions
 *
 *
 ***************************************************************
 */

#include <stdio.h>
#include <stdlib.h>


#include "pss.h"
#include "../src/insert_info.h"
#include "../src/sub_reg.h"
#include "../src/prune.h"
#include "../src/consume.h"
#include "../src/delete.h"
#include "../src/print.h"


struct Group* groups[MG];
struct SubInfo* subinfo[MG];
struct TreeInfo* old[MG];
int m;
int p;
int y;
int noGroups = 0;
int noSubs = 0;

/**
 * @brief Hash Function.
 *        Formula: (ax + b) mod c, where a is the prime number,
 *        b is the random number, and
 *        c is the size of the hast table.
 * 
 * @param x the id of the subscriber
*/
int h(int x){
    /* */
    /*
    return x % 10;
    */
    return (p * x + y) % m;
}

/**
 * @brief Optional function to initialize data structures that
 *        need initialization
 *
 * @param m Size of the hash table.
 * @param p Prime number for the universal hash functions.
 *
 * @return 0 on success
 *         1 on failure
 */
int initialize(int M, int P){
    int i;
    m = M; p = P;

    srand(time(NULL));
    y = rand();
    
    for(i = 0; i < MG; i++){
        groups[i] = (struct Group*)malloc(sizeof(struct Group));
        if(groups[i] == NULL) return EXIT_FAILURE;
        groups[i]->gId = i;
        groups[i]->gsub = NULL;
        groups[i]->gr = NULL;
    }

    for(i = 0; i < m; i++){
        subinfo[i] = NULL;
    }

    return EXIT_SUCCESS;
}

/**
 * @brief Free resources
 *
 * @return 0 on success
 *         1 on failure
 */
int free_all(void){
    int i;
    struct SubInfo* current;

    for(i = 0; i < MG; i++){
        free(groups[i]);
    }

    for(i = 0; i < m; i++){
        current = subinfo[h(i)];
        while(current != NULL){
            free(current);
            current = current->snext;
        }
    }

    return EXIT_SUCCESS;
}

/**
 * @brief Insert info
 *
 * @param iTM Timestamp of arrival
 * @param iId Identifier of information
 * @param gids_arr Pointer to array containing the gids of the Event.
 * @param size_of_gids_arr Size of gids_arr including -1
 * @return 0 on success
 *          1 on failure
 */
int Insert_Info(int iTM,int iId,int* gids_arr,int size_of_gids_arr){
    int result;
    result = handle_insert(iTM, iId, gids_arr, size_of_gids_arr);
    return result;
}
/**
 * @brief Subsriber Registration
 *
 * @param sTM Timestamp of arrival
 * @param sId Identifier of subscriber
 * @param gids_arr Pointer to array containing the gids of the Event.
 * @param size_of_gids_arr Size of gids_arr including -1
 * @return 0 on success
 *          1 on failure
 */
int Subscriber_Registration(int sTM,int sId,int* gids_arr,int size_of_gids_arr){
    int result;
    result = handle_sub_reg(sTM, sId, gids_arr, size_of_gids_arr);
    return result;
}
/**
 * @brief Prune Information from server and forward it to client
 *
 * @param tm Information timestamp of arrival
 * @return 0 on success
 *          1 on failure
 */
int Prune(int tm){
    int result;
    result = handle_prune(tm);
    return result;
}
/**
 * @brief Consume Information for subscriber
 *
 * @param sId Subscriber identifier
 * @return 0 on success
 *          1 on failure
 */
int Consume(int sId){
    int result;
    result = handle_consume(sId);
    return result;
}
/**
 * @brief Delete subscriber
 *
 * @param sId Subscriber identifier
 * @return 0 on success
 *          1 on failure
 */
int Delete_Subscriber(int sId){
    int result;
    result = handle_delete(sId);
    return result;
}
/**
 * @brief Print Data Structures of the system
 */
Print_all(void){
    handle_print();
}

struct SubInfo* findSub(int id){
    struct SubInfo* current;
    int i;

    for(i = 0; i < m; i++){
        current = subinfo[h(i)];
        while(current != NULL){
            if(current->sId == id){
                return current;
            }
            current = current->snext;
        }
    }

    return NULL;
}