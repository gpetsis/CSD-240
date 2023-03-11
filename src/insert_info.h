#ifndef insert
#define insert

#include "../main/pss.h"

/**
 * @brief Function to insert the node new recursively.
 * 
 * @param root the root of the info tree
 * @param new the node to be inserted
 * 
 * @return the tree with the new node inserted
*/
struct Info* insert_rec(struct Info* root, struct Info* new);

/**
 * @brief Function to print the ids of a tree inorder.
 * 
 * @param root the root of the tree
*/
int inorder(struct Info* root);

/**
 * @brief Function to handle the event insert info.
 * 
 * @param tm the timestamp of the information
 * @param id the id of the information
 * @param gp the groups in which the info relates
 * @param num the number of groups
 * 
 * @return 0 on success
 *         1 on failure 
*/
int handle_insert(int tm, int id, int* gp, int num);

/**
 * @brief Simple bubble sort.
 * 
 * @param array the array of groups
 * @param n the number of groups
 * 
 * @return the array sorted in ascending order
*/
int* bubbleSort(int array[], int n);

/**
 * @brief Function to print the results of the insert.
 * 
 * @param gp the groups its interested
 * @param num the number of the groups its interested
*/
void Print_insert(int* gp, int num);

#endif