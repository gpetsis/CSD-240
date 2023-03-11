#ifndef consume
#define consume

#include "../main/pss.h"

/**
 * @brief Function to point a node to the righest leaf.
 * 
 * @param root the root of the tree
 * 
 * @return a pointer to the rightest leaf of the tree
*/
struct TreeInfo* pointToRightest(struct TreeInfo* root);

/**
 * @brief Function to handle the consume event.
 * 
 * @param id the id of the subscriber
 * 
 * @return 0 on success, 1 on failure
*/
int handle_consume(int id);

/**
 * @brief Function to print the leaves for the consume event.
 * 
 * @param root the root of the consume tree
 * @param id the id of the subscriber
 * @param gid the id of the group
*/
void consume_print_leaves(struct TreeInfo* root, int id, int gid);

/**
 * @brief Function to print the results of the event consume.
 * 
 * @param id the id of the subscriber
*/
void Print_consume(int id);

#endif