#ifndef queue_h
#define queue_h

#include <stdio.h>
#include "rbt.h"

typedef struct queue QUEUE;

extern int empty();
extern void pop();
extern NODE* peak();
extern void enqueue(NODE*);

#endif
