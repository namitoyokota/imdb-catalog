#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "queue.h"

enum type {RED,BLACK};

struct node
{
    enum type color;
    NODE* left;
    NODE* right;
    NODE* parent;

    bool enable;
    int index;
    char* title;
    int year;
    int runtime;
    char *genres;
};

void LeftRotate(NODE** T,NODE** x)
{
    NODE* y = (*x)->right;
    (*x)->right = y->left;

    if(y->left!=NULL)
        y->left->parent = *x;

    y->parent = (*x)->parent;

    if((*x)->parent == NULL)
        *T = y;

    else if(*x == (*x)->parent->left)
        (*x)->parent->left = y;

    else
        (*x)->parent->right = y;

    y->left = *x;

    (*x)->parent = y;

}
void RightRotate(NODE** T,NODE** x)
{
    NODE* y = (*x)->left;
    (*x)->left = y->right;

    if(y->right!=NULL)
        y->right->parent = *x;

    y->parent = (*x)->parent;

    if((*x)->parent==NULL)
        *T = y;

    else if((*x)== (*x)->parent->left)
        (*x)->parent->left = y;

    else
        (*x)->parent->right = y;

    y->right = *x;
    (*x)->parent = y;

}

void RB_insert_fixup(NODE** T, NODE** z)
{
    NODE* grandparent = NULL;
    NODE* parentpt = NULL;

    while(((*z)!=*T)&& ((*z)->color!= BLACK) && ((*z)->parent->color == RED))
    {
        parentpt = (*z)->parent;
        grandparent = (*z)->parent->parent;

        if(parentpt == grandparent->left)
        {
            NODE* uncle = grandparent->right;

            if(uncle!=NULL && uncle->color == RED)
            {
                grandparent->color = RED;
                parentpt->color = BLACK;
                uncle->color = BLACK;
                *z = grandparent;
            }

            else
            {
                if((*z) == parentpt->right)
                {
                    LeftRotate(T,&parentpt);
                    (*z) = parentpt;
                    parentpt = (*z)->parent;
                }

                RightRotate(T,&grandparent);
                parentpt->color = BLACK;
                grandparent->color = RED;
                (*z) = parentpt;
            }
        }

        else
        {
            NODE* uncle = grandparent->left;

            if(uncle!=NULL && uncle->color == RED)
            {
                grandparent->color = RED;
                parentpt->color = BLACK;
                uncle->color = BLACK;
                (*z) = grandparent;
            }

            else
            {
                if((*z) == parentpt->left)
                {
                    RightRotate(T,&parentpt);
                    (*z) = parentpt;
                    parentpt = (*z)->parent;
                }

                LeftRotate(T,&grandparent);
                parentpt->color = BLACK;
                grandparent->color = RED;
                (*z) = parentpt;
            }
        }
    }
    (*T)->color = BLACK;

}

void index_to_title(NODE* root, NODE** RBT_title)  {

    if(root==NULL)
        return;

    index_to_title(root->left, RBT_title);
    *RBT_title = RB_insert_title(*RBT_title, root->enable, root->index, root->title, root->year, root->runtime, root->genres);
	index_to_title(root->right, RBT_title);
}

void index_to_year(NODE* root, NODE** RBT_year)  {

    if(root==NULL)
        return;

    index_to_year(root->left, RBT_year);
    *RBT_year = RB_insert_year(*RBT_year, root->enable, root->index, root->title, root->year, root->runtime, root->genres);
	index_to_year(root->right, RBT_year);
}

void index_to_runtime(NODE* root, NODE** RBT_runtime)  {

    if(root==NULL)
        return;

    index_to_runtime(root->left, RBT_runtime);
    *RBT_runtime = RB_insert_runtime(*RBT_runtime, root->enable, root->index, root->title, root->year, root->runtime, root->genres);
	index_to_runtime(root->right, RBT_runtime);
}

NODE* RB_insert(NODE* T, bool enable, int index, char* title, int year, int runtime, char *genres)
{
    NODE* z = (NODE*)malloc(sizeof(struct node));
    z->enable = enable;
    z->index = index;
    z->title = title;
    z->year = year;
    z->runtime = runtime;
    z->genres = genres;
    z->left = NULL;
    z->right = NULL;
    z->parent = NULL;
    z->color = RED;

    NODE* y = NULL;
    NODE* x = T;//root

    while(x!=NULL)
    {
        y = x;
        if(z->index < x->index)
            x = x->left;

        else
            x = x->right;
    }
    z->parent = y;

    if(y==NULL)
        T = z;

    else if(z->index < y->index)
        y->left = z;

    else
        y->right = z;

    RB_insert_fixup(&T,&z);

    return T;
}

NODE* RB_insert_title(NODE* T, bool enable, int index, char* title, int year, int runtime, char *genres)
{
    NODE* z = (NODE*)malloc(sizeof(struct node));
    z->enable = enable;
    z->index = index;
    z->title = title;
    z->year = year;
    z->runtime = runtime;
    z->genres = genres;
    z->left = NULL;
    z->right = NULL;
    z->parent = NULL;
    z->color = RED;

    NODE* y = NULL;
    NODE* x = T;//root

    while(x!=NULL)
    {
        y = x;
        if(strcmp(z->title,x->title) < 0)
            x = x->left;

        else
            x = x->right;
    }
    z->parent = y;

    if(y==NULL)
        T = z;

    else if(strcmp(z->title, y->title) < 0)
        y->left = z;

    else
        y->right = z;

    RB_insert_fixup(&T,&z);

    return T;
}

NODE* RB_insert_year(NODE* T, bool enable, int index, char* title, int year, int runtime, char *genres)
{
    NODE* z = (NODE*)malloc(sizeof(struct node));
    z->enable = enable;
    z->index = index;
    z->title = title;
    z->year = year;
    z->runtime = runtime;
    z->genres = genres;
    z->left = NULL;
    z->right = NULL;
    z->parent = NULL;
    z->color = RED;

    NODE* y = NULL;
    NODE* x = T;//root

    while(x!=NULL)
    {
        y = x;
        if(z->year < x->year)
            x = x->left;

        else
            x = x->right;
    }
    z->parent = y;

    if(y==NULL)
        T = z;

    else if(z->year < y->year)
        y->left = z;

    else
        y->right = z;

    RB_insert_fixup(&T,&z);

    return T;
}

NODE* RB_insert_runtime(NODE* T, bool enable, int index, char* title, int year, int runtime, char *genres)
{
    NODE* z = (NODE*)malloc(sizeof(struct node));
    z->enable = enable;
    z->index = index;
    z->title = title;
    z->year = year;
    z->runtime = runtime;
    z->genres = genres;
    z->left = NULL;
    z->right = NULL;
    z->parent = NULL;
    z->color = RED;

    NODE* y = NULL;
    NODE* x = T;//root

    while(x!=NULL)
    {
        y = x;
        if(z->runtime < x->runtime)
            x = x->left;

        else
            x = x->right;
    }
    z->parent = y;

    if(y==NULL)
        T = z;

    else if(z->runtime < y->runtime)
        y->left = z;

    else
        y->right = z;

    RB_insert_fixup(&T,&z);

    return T;
}

NODE* Tree_minimum(NODE* node)
{
    while(node->left!=NULL)
        node = node->left;

    return node;
}

void RB_delete_fixup(NODE** T, NODE** x)
{
    while((*x)!=*T && (*x)->color == BLACK)
    {
        if((*x)==(*x)->parent->left)
        {
            NODE* w = (*x)->parent->right;

            if(w->color==RED)
            {
                w->color = BLACK;
                (*x)->parent->color = BLACK;
                LeftRotate(T,&((*x)->parent));
                w = (*x)->parent->right;
            }

            if(w->left->color==BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                (*x) = (*x)->parent;
            }

            else
            {
                if(w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    RightRotate(T,&w);
                    w = (*x)->parent->right;
                }

                w->color = (*x)->parent->color;
                (*x)->parent->color = BLACK;
                w->right->color = BLACK;
                LeftRotate(T,&((*x)->parent));
                (*x) = *T;
            }
        }

        else
        {
            NODE* w = (*x)->parent->left;

            if(w->color==RED)
            {
                w->color = BLACK;
                (*x)->parent->color = BLACK;
                RightRotate(T,&((*x)->parent));
                w = (*x)->parent->left;
            }

            if(w->right->color==BLACK && w->left->color == BLACK)
            {
                w->color = RED;
                (*x) = (*x)->parent;
            }

            else
            {
                if(w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    LeftRotate(T,&w);
                    w = (*x)->parent->left;
                }

                w->color = (*x)->parent->color;
                (*x)->parent->color = BLACK;
                w->left->color = BLACK;
                RightRotate(T,&((*x)->parent));
                (*x) = *T;
            }
        }
    }
    (*x)->color = BLACK;

}

void RB_transplat(NODE** T, NODE** u,NODE** v)
{
    if((*u)->parent == NULL)
        *T = *v;

    else if((*u)==(*u)->parent->left)
        (*u)->parent->left = *v;
    else
        (*u)->parent->right = *v;

    if((*v)!=NULL) 
        (*v)->parent = (*u)->parent;
}

NODE* RB_delete(NODE* T,NODE* z)
{
    NODE* y = z;
    enum type yoc;
    yoc = z->color; // y's original color

    NODE* x;

    if(z->left==NULL )
    {
        x = z->right;
        RB_transplat(&T,&z,&(z->right));
    }

    else if(z->right==NULL )
    {
        x = z->left;
        RB_transplat(&T,&z,&(z->left));
    }

    else
    {
        y = Tree_minimum(z->right);
        yoc = y->color;
        x = y->right;

        if(y->parent==z)
            x->parent = y;

        else
        {
            RB_transplat(&T,&y,&(y->right));
            y->right = z->right;
            y->right->parent = y;
        }

        RB_transplat(&T,&z,&y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if(yoc==BLACK)
        RB_delete_fixup(&T,&x);

    return T;
}

NODE* BST_search(NODE* root, int x)
{
    if(root==NULL || root->index == x)
        return root;
    else if (root->index > x)
       return  BST_search(root->left,x);
    else
        return BST_search(root->right,x);
}

void inorder(NODE* root)
{
    if(root==NULL)
        return;
    inorder(root->left);
	printf("%d\t%d\t%s\t%d\t%d\t%s\n", root->enable, root->index, root->title, root->year, root->runtime, root->genres);
	inorder(root->right);
}

void outorder(NODE* root)
{
    if(root==NULL)
        return;
    outorder(root->right);
	printf("%d\t%d\t%s\t%d\t%d\t%s\n", root->enable, root->index, root->title, root->year, root->runtime, root->genres);
	outorder(root->left);
}

void inorder_deleted(NODE* root) {
    if (root==NULL)
        return;
    inorder_deleted(root->left);
    if (root->enable == 0)
	    printf("%d\t%d\t%s\t%d\t%d\t%s\n", root->enable, root->index, root->title, root->year, root->runtime, root->genres);
    inorder_deleted(root->right);
}

void inorder_year_bigger(NODE* root, int year) {
    if (root==NULL)
        return;
    inorder_year_bigger(root->left, year);
    if (root->year > year)
	    printf("%d\t%d\t%s\t%d\t%d\t%s\n", root->enable, root->index, root->title, root->year, root->runtime, root->genres);
    inorder_year_bigger(root->right, year);
}

void inorder_year_smaller(NODE* root, int year) {
    if (root==NULL)
        return;
    inorder_year_smaller(root->left, year);
    if (root->year < year)
	    printf("%d\t%d\t%s\t%d\t%d\t%s\n", root->enable, root->index, root->title, root->year, root->runtime, root->genres);
    inorder_year_smaller(root->right, year);
}

void inorder_runtime_bigger(NODE* root, int runtime) {
    if (root==NULL)
        return;
    inorder_runtime_bigger(root->left, runtime);
    if (root->runtime > runtime)
	    printf("%d\t%d\t%s\t%d\t%d\t%s\n", root->enable, root->index, root->title, root->year, root->runtime, root->genres);
    inorder_runtime_bigger(root->right, runtime);
}

void inorder_runtime_smaller(NODE* root, int runtime) {
    if (root==NULL)
        return;
    inorder_runtime_smaller(root->left, runtime);
    if (root->runtime < runtime)
	    printf("%d\t%d\t%s\t%d\t%d\t%s\n", root->enable, root->index, root->title, root->year, root->runtime, root->genres);
    inorder_runtime_smaller(root->right, runtime);
}

void inorder_genres(NODE* root, char* genres) {
     if (root==NULL)
        return;
    inorder_genres(root->left, genres);
    if (strstr(root->genres,genres) != NULL)
	    printf("%d\t%d\t%s\t%d\t%d\t%s\n", root->enable, root->index, root->title, root->year, root->runtime, root->genres);
    inorder_genres(root->right, genres);
}

// doesnt work
NODE* search_title(NODE* root, char* str) {

    if(root==NULL || strcmp(root->title,str)==0)
        return root;
    else if (strcmp(root->title, str) > 0)
        return  search_title(root->left,str);
    else
        return search_title(root->right,str);
}

void printNode(NODE* root) {
    if (root != NULL)
	    printf("%d\t%d\t%s\t%d\t%d\t%s\n\n", root->enable, root->index, root->title, root->year, root->runtime, root->genres);
}

// update
void update_index(NODE* root, int index) {
    root->index = index;
}
void update_title(NODE* root, char* str) {
    root->title = str;
}
void update_year(NODE* root, int year) {
    root->year = year;
}
void update_runtime(NODE* root, int runtime) {
    root->runtime = runtime;
}
void update_genres(NODE* root, char* genres) {
    root->genres = genres;
}
void update_enable(NODE* root, bool enable) {
    root->enable = enable;
}

/*
// sort
NODE* sort_index(NODE* root) {}
NODE* sort_title(NODE* root) {}
NODE* sort_year(NODE* root) {}
NODE* sort_runtime(NODE* root) {}
// filter
NODE* filter_genres(NODE* root) {}
*/