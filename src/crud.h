#ifndef crud_h
#define crud_h

#include <stdio.h>
#include "rbt.h"

extern void createData(NODE**, char*, char*, char*, char*, char*);
extern void retrieveData(NODE**, char*);
extern void updateData(NODE**, char*, char*, char*, char*, char*);
extern void deleteData(NODE**, char*);

#endif
