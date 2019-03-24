#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <curses.h>
#include "../lib/stack.h"

struct stack {
	bool enable;
    int index;
    char* title;
    int year;
    int runtime;
    char* genres;
    char* media;
    int m;
    int d;
    int y;
	STACK* next;
};
STACK* top;
int MAX;

void push(bool enable, int index, char* title, int year, int runtime, char *genres, char* media, int m, int d, int y)
{
    STACK* temp = (STACK*)malloc(sizeof(struct stack));
    temp->enable = enable;
    temp->index = index;
    temp->title = title;
    temp->year = year;
    temp->runtime = runtime;
    temp->genres = genres;
    temp->media = media;
    temp->m = m;
    temp->d = d;
    temp->y = y;
	temp->next = top;
	top = temp;
}

void pop(WINDOW* win, int y)
{
	if(empty()){
		printf("Error: Stack is empty");
		return;
	}

    mvwprintw(win, y, 2, "%d\t%s\t%d\t%d\t%s\t%s\t%d/%d/%d", top->index, top->title, top->year, top->runtime, top->genres, top->media, top->m, top->d, top->y);

	STACK* temp;
	temp = top;
	temp = temp->next;
	top = temp;
}

bool empty() {
    if (top == NULL) return true;
    else return false;
}

void setMax(int max) {
    MAX = max;
}

void freeStack() {
    top = NULL;
}