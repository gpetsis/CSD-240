#include <stdio.h>
#include <stdlib.h>

#include "print.h"
#include "prune.h"

void handle_print(){
    noGroups = 0;
    noSubs = 0;

    printInfoSublist();
    printSubTreelist();
    printf("    NO_GROUPS=<%d>, NO_SUBSCRIBERS=<%d>\n", noGroups, noSubs);
}