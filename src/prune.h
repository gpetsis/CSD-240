#ifndef prune
#define prune

#include "../main/pss.h"

/**
 * @brief Function to create a new TreeInfo node.
 * 
 * @param id the id of the node
 * @param tm the timestamp of the node
 * 
 * @return the address to where the new node is created
*/
struct TreeInfo* newTree(int id, int tm);

/**
 * @brief Function to find the next inorder successor.
 * 
 * @param node the root of the Info tree
 * 
 * @return the address of the node
*/
struct Info* minValueNode(struct Info* node);

/**
 * @brief Function to delete a node from a tree.
 * 
 * @param root the root of the tree
 * @param tm the timestamp of the node we want to delete
 * 
 * @return the root of the tree with the node deleted
*/
struct Info* delete_Node(struct Info* root, int tm);

/**
 * @brief Function to delete nodes with the same id in a tree.
 * 
 * @param root the root of the tree
 * 
 * @return the root of the tree with the duplicates deleted
*/
struct Info* delete_multiples(struct Info* root);

/**
 * @brief Function to insert a node to a leaf oriented binary search tree.
 * 
 * @param root the root of the tree we want to insert the node
 * @param id the id of the new node
 * @param tm the timestamp of the new node
 * 
 * @return the root of the tree with the new node inserted
*/
struct TreeInfo* insert_leaf_oriented(struct TreeInfo* root, int id, int tm);

/**
 * @brief Function to delete all nodes that have their timestamp less or equal to the given timestamp.
 * 
 * @param root the root of the tree
 * @param tm the timestamp limit
 * @param gid the group of the Info tree
 * 
 * @return the root of the tree with the nodes that have tm less than the given tm deleted
*/
struct Info* delete_Info(struct Info* root, int tm, int gid);

/**
 * Function to handle the event prune.
 * 
 * @param tm the timestamp for the infos we want to free
 * 
 * @return 0 on success, 1 on failure 
*/
int handle_prune(int tm);

/**
 * @brief Function to print the treeinfo nodes inorder.
 * 
 * @param root the root of the tree
 * 
 * @return 1 if nothing was printed, 0 otherwise
*/
int inorderT(struct TreeInfo* root);

/**
 * @brief Function to print the leaves of a leaf oriented binary search tree
 * 
 * @param root the root of the tree
 *
 * @return 1 if nothing was printed, 0 otherwise
*/
int printLeafs(struct TreeInfo* root, int gid);

/**
 * Function to print the results of the event prune.
*/
void Print_prune();

#endif