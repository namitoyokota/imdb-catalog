#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "bst.h"
//#include "queue.h"

struct node
{
	bool enable;
	int index;
	char *type;
	char *title;
	bool adult;
	char *startYear;
	char *endYear;
	char *runtime;
	char *genres;
	NODE* left;
	NODE* right;
};

NODE* NewNODE (int index, char* type, char* title, char* adult, char* startYear, char* endYear, char* runtime, char* genres)
{
	NODE* temp = (NODE*)malloc(sizeof(NODE));
	temp->enable = true;
	temp->index = index;
	temp->type = type;
	temp->title = title;
	temp->adult = atoi(adult);
	temp->startYear = startYear;
	temp->endYear = endYear;
	temp->runtime = runtime;
	temp->genres = genres;
	temp->left = NULL;
	temp->right = NULL;

	return temp;
}

NODE* insert (int sort, NODE* bst, int index, char* type, char* title, char* adult, char* startYear, char* endYear, char* runtime, char* genres)
{
	if (bst==NULL) {
		bst =  NewNODE(index, type, title, adult, startYear, endYear, runtime, genres);
		return bst;
	}

	switch(sort) {
		case 1 : // insert by index
			if (index <= bst->index)
				bst->left = insert(sort, bst->left, index, type, title, adult, startYear, endYear, runtime, genres);
			else
				bst->right = insert(sort, bst->right, index, type, title, adult, startYear, endYear, runtime, genres);
			break;

		case 3 : // insert by title
			for (int i=0; i<(int)strlen(title); i++) {
				if (title[i] == bst->title[i]) continue;
				else if (title[i] < bst->title[i]) {
					bst->left = insert(sort, bst->left, index, type, title, adult, startYear, endYear, runtime, genres);
					break;
				}
				else if (title[i] > bst->title[i]) {
					bst->right = insert(sort, bst->right, index, type, title, adult, startYear, endYear, runtime, genres);
					break;
				}
			}
			break;

		case 6 : // insert by start year
			for (int i=0; i<(int)strlen(startYear); i++) {
				if (startYear[i] == bst->startYear[i]) continue;
				else if (startYear[i] < bst->startYear[i]) {
					bst->left = insert(sort, bst->left, index, type, title, adult, startYear, endYear, runtime, genres);
					break;
				}
				else if (startYear[i] > bst->startYear[i]) {
					bst->right = insert(sort, bst->right, index, type, title, adult, startYear, endYear, runtime, genres);
					break;
				}
			}
			break;
		
		case 7 : // insert by end year
			for (int i=0; i<(int)strlen(endYear); i++) {
				if (endYear[i] == bst->endYear[i]) continue;
				else if (endYear[i] < bst->endYear[i]) {
					bst->left = insert(sort, bst->left, index, type, title, adult, startYear, endYear, runtime, genres);
					break;
				}
				else if (endYear[i] > bst->endYear[i]) {
					bst->right = insert(sort, bst->right, index, type, title, adult, startYear, endYear, runtime, genres);
					break;
				}
			}
			break;
		
		case 8 : // insert by end year
			for (int i=0; i<(int)strlen(runtime); i++) {
				if (runtime[i] == bst->runtime[i]) continue;
				else if (runtime[i] < bst->runtime[i]) {
					bst->left = insert(sort, bst->left, index, type, title, adult, startYear, endYear, runtime, genres);
					break;
				}
				else if (runtime[i] > bst->runtime[i]) {
					bst->right = insert(sort, bst->right, index, type, title, adult, startYear, endYear, runtime, genres);
					break;
				}
			}
			break;

		default:
			break;
	}

	return bst;
}

void InOrder (NODE* bst)
{
	if (bst==NULL)
		return;

	InOrder(bst->left);
	printf("\n%d \t %d \t %s \t %s \t %d \t %s \t %s \t %s \t %s", bst->enable, bst->index, bst->type, bst->title, bst->adult, bst->startYear, bst->endYear, bst->runtime, bst->genres);
	InOrder(bst->right);
}

void NotOrder (NODE* bst)
{
	if (bst==NULL)
		return;

	NotOrder(bst->right);
	printf("\n%d \t %d \t %s \t %s \t %d \t %s \t %s \t %s \t %s", bst->enable, bst->index, bst->type, bst->title, bst->adult, bst->startYear, bst->endYear, bst->runtime, bst->genres);
	NotOrder(bst->left);
}