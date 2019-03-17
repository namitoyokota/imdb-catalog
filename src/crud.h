#ifndef crud_h
#define crud_h

#include <stdio.h>
#include "rbt.h"

extern void CREATE_MOVIE(NODE**, char*, char*, char*, char*, char*, char*, int, int, int);
extern void RETRIEVE_MOVIE(NODE**, char*);
extern void UPDATE_MOVIE(NODE**, char*, char*, char*, char*, char*, char*, int, int, int);
extern void DELETE_MOVIE(NODE**, char*);

#endif
