#ifndef crud_h
#define crud_h

#include <stdio.h>
#include "../lib/rbt.h"

extern void CREATE_MOVIE(char*, RBT**, char*, char*, char*, char*, char*, char*, char*, char*, char*);
extern void RETRIEVE_MOVIE(char*, RBT**, char*);
extern void UPDATE_MOVIE(char*, RBT**, char*, char*, char*, char*, char*, char*, char*, char*, char*);
extern void DELETE_MOVIE(char*, RBT**, char*);

#endif
