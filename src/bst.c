#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bst.h"
#include "queue.h"

struct node
{
	bool enable;
	int index;
	char *title;
	char *type;
	char *genres;
	NODE* left;
	NODE* right;
};

NODE* NewNODE(int index, char* title, char* type, char* genres)
{
	NODE* temp = (NODE*)malloc(sizeof(NODE));
	temp->enable = true;
	temp->index = index;
	temp->title = title;
	temp->type = type;
	temp->genres = genres;
	temp->left = NULL;
	temp->right = NULL;

	return temp;
}

NODE* insert(NODE* bst, int index, char* title, char* type, char* genres)
{
	if(bst==NULL)
		bst =  NewNODE(index, title, type, genres);

	else if(index <= bst->index)
		bst->left = insert(bst->left,index, title, type, genres);
	
	else bst->right = insert(bst->right,index, title, type, genres);

	return bst;

}

NODE* Delete(NODE* bst,int index)
{
	if(bst==NULL)
		return bst;

	else if(index < bst->index)
		bst->left = Delete(bst->left,index);

	else if(index > bst->index)
		bst->right = Delete(bst->right,index);

	else
	{
		if(bst->left==NULL && bst->right==NULL)
		{
			free(bst);
			bst = NULL;
		}

		else if(bst->left!=NULL && bst->right==NULL)
		{
			NODE* temp = bst->left;
			free(temp);
			bst = bst->left;
		}
		else if(bst->right!=NULL&& bst->left==NULL)
		{
			NODE* temp = bst->right;
			free(temp);
			bst = bst->right;
		}

		else
		{
			NODE* temp = FindMin(bst->right);
			bst->index = temp->index;
			bst->right = Delete(bst->right,temp->index); 
		}

	}
	return bst;
}

NODE* FindMin(NODE* bst)
{
	while(bst->left!=NULL)
		bst = bst->left;

	return bst;
}

void PreOrder(NODE* bst)
{
	if(bst==NULL)
		return;

	printf("\n%d, %d, %s, %s, %s", bst->enable, bst->index, bst->title, bst->type, bst->genres);
	PreOrder(bst->left);
	PreOrder(bst->right);
}

void InOrder(NODE* bst)
{
	if(bst==NULL)
		return;

	InOrder(bst->left);
	printf("\n%d, %d, %s, %s, %s", bst->enable, bst->index, bst->title, bst->type, bst->genres);
	InOrder(bst->right);
}

void PostOrder(NODE* bst)
{
	if(bst==NULL)
		return;

	PostOrder(bst->left);
	PostOrder(bst->right);
	printf("\n%d, %d, %s, %s, %s", bst->enable, bst->index, bst->title, bst->type, bst->genres);
}


void traverse(NODE* bst)
{
	printf("\nPreOrder traversal : "); PreOrder(bst);
	printf("\n\nInorder traversal  :   "); InOrder(bst);
	printf("\n\nPostOrder traversal:   "); PostOrder(bst);
	printf("\n");
}