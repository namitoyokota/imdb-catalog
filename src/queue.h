#ifndef queue_h
#define queue_h

#include <stdio.h>

typedef struct queue QUEUE;

extern int isEmpty();
extern void Pop();
extern NODE* Pfront();
extern void Enqeue(NODE*);

#endif
