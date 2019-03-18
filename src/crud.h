#ifndef crud_h
#define crud_h

#include <stdio.h>
#include "rbt.h"

extern void CREATE_MOVIE(char*, NODE**, char*, char*, char*, char*, char*, char*, char*, char*, char*);
extern void RETRIEVE_MOVIE(char*, NODE**, char*);
extern void UPDATE_MOVIE(char*, NODE**, char*, char*, char*, char*, char*, char*, char*, char*, char*);
extern void DELETE_MOVIE(char*, NODE**, char*);

#endif
