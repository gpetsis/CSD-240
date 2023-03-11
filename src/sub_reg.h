#ifndef subreg
#define subreg

#include "../main/pss.h"

/**
 * @brief Function to handle the subscriber registration event.
 * 
 * @param tm the timestamp of the subscriber
 * @param id the id of the subscriber
 * @param gp the groups the subscriber is interested
 * 
 * @return 0 on success, 1 on failure
*/
int handle_sub_reg(int tm, int id, int* gp, int num);

/**
 * @brief Function to print the results of the subscriber registration.
 * 
 * @param gp the groups its headed
 * @param num the number of the groups its headed
*/
void Print_sub_reg(int* gp, int num);

#endif