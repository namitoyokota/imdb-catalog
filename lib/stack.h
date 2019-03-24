#ifndef stack_h
#define stack_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../lib/stack.h"
#define MAXS 101

typedef struct stack STACK;

void push(bool enable, int index, char* title, int year, int runtime, char *genres, char* media, int m, int d, int y);
void pop(WINDOW*, int);
bool empty();
void setMax(int);
void freeStack();

#endif