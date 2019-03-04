#ifndef bst_h
#define bst_h

#include <stdio.h>

typedef struct node NODE;

extern NODE* NewNODE(int, char*, char*, char*, char*, char*, char*, char*);
extern void PostOrder(NODE*);
extern NODE* FindMin(NODE*);
extern void LevelOrder(NODE*);
extern NODE* Delete(NODE*,int);
extern void InOrder(NODE*);
extern void NotOrder(NODE*);
extern void PreOrder(NODE*);
extern NODE* insert(int, NODE*, int, char*, char*, char*, char*, char*, char*, char*);
extern void traverse(NODE*);

#endif
