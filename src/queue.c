#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "queue.h"

struct queue
{
	NODE* data;
	QUEUE* next;
};

QUEUE* front = NULL;
QUEUE* rear = NULL;

int isEmpty()
{
	if(front==NULL)
		return 1;
	else
		return 0;
}

void Pop()
{
	if(isEmpty())
		return;

	QUEUE* temp = front;
	front = front->next;
	free(temp);
}

NODE* Pfront()
{
	NODE* temp ;
	temp = front->data;
	return temp;
}

void Enqeue(NODE* data)
{
	QUEUE* temp;
	temp = (QUEUE*)malloc(sizeof(QUEUE));
	temp->data = data;
	temp->next=NULL;

	if(front==NULL && rear==NULL)
	{
		front = rear = temp;
		return;
	}

	rear->next = temp;
	rear =temp;
}
