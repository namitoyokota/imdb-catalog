#ifndef rbt_h
#define rbt_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node NODE;

void LeftRotate(NODE** T,NODE** x);
void RightRotate(NODE** T,NODE** x);
void RB_insert_fixup(NODE** T, NODE** z);
void index_to_title(NODE*, NODE**);
void index_to_year(NODE*, NODE**);
void index_to_runtime(NODE*, NODE**);
NODE* RB_insert(NODE* T, bool enable, int index, char* title, int year, int runtime, char *genres);
NODE* RB_insert_title(NODE* T, bool enable, int index, char* title, int year, int runtime, char *genres);
NODE* RB_insert_year(NODE* T, bool enable, int index, char* title, int year, int runtime, char *genres);
NODE* RB_insert_runtime(NODE* T, bool enable, int index, char* title, int year, int runtime, char *genres);
NODE* RB_insert_genres(NODE* T, bool enable, int index, char* title, int year, int runtime, char *genres);
void inorder(NODE* root);
void outorder(NODE* root);
NODE* Tree_minimum(NODE* node);
void RB_delete_fixup(NODE** T, NODE** x);
void RB_transplat(NODE** T, NODE** u,NODE** v);
NODE* RB_delete(struct node *T,NODE* z);
NODE* BST_search(NODE* root, int x);
void printNode(NODE*);

// search
NODE* search_title(NODE*, char*);

// update
void update_index(NODE*, int);
void update_title(NODE*, char*);
void update_year(NODE*, int);
void update_runtime(NODE*, int);
void update_genres(NODE*, char*);
void update_enable(NODE*, bool);

/*
// sort
NODE* sort_index(NODE*);
NODE* sort_title(NODE*);
NODE* sort_year(NODE*);
NODE* sort_runtime(NODE*);
// filter
NODE* filter_genres(NODE*);
*/

#endif
