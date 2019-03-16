#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "rbt.h"

enum type {RED,BLACK};

struct node {
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

// MAIN
void LEFT_ROTATE(NODE** T,NODE** x) {
    NODE* y = (*x)->right;
    (*x)->right = y->left;
    if (y->left!=NULL)
        y->left->parent = *x;
    y->parent = (*x)->parent;
    if ((*x)->parent == NULL)
        *T = y;
    else if(*x == (*x)->parent->left)
        (*x)->parent->left = y;
    else (*x)->parent->right = y;
    y->left = *x;
    (*x)->parent = y;
}
void RIGHT_ROTATE(NODE** T,NODE** x) {
    NODE* y = (*x)->left;
    (*x)->left = y->right;
    if (y->right!=NULL)
        y->right->parent = *x;
    y->parent = (*x)->parent;
    if ((*x)->parent==NULL)
        *T = y;
    else if ((*x)== (*x)->parent->left)
        (*x)->parent->left = y;
    else (*x)->parent->right = y;
    y->right = *x;
    (*x)->parent = y;
}
NODE* TREE_MINIMUM(NODE* node) {
    while (node->left!=NULL)
        node = node->left;
    return node;
}

// INSERT
void RB_INSERT_FIXUP(NODE** T, NODE** z) {
    NODE* grandparent = NULL;
    NODE* parentpt = NULL;

    while (((*z)!=*T)&& ((*z)->color!= BLACK) && ((*z)->parent->color == RED)) {
        parentpt = (*z)->parent;
        grandparent = (*z)->parent->parent;
        if (parentpt == grandparent->left) {
            NODE* uncle = grandparent->right;
            if (uncle!=NULL && uncle->color == RED) {
                grandparent->color = RED;
                parentpt->color = BLACK;
                uncle->color = BLACK;
                *z = grandparent;
            } else {
                if ((*z) == parentpt->right) {
                    LEFT_ROTATE(T,&parentpt);
                    (*z) = parentpt;
                    parentpt = (*z)->parent;
                }
                RIGHT_ROTATE(T,&grandparent);
                parentpt->color = BLACK;
                grandparent->color = RED;
                (*z) = parentpt;
            }
        } else {
            NODE* uncle = grandparent->left;
            if (uncle!=NULL && uncle->color == RED) {
                grandparent->color = RED;
                parentpt->color = BLACK;
                uncle->color = BLACK;
                (*z) = grandparent;
            } else {
                if ((*z) == parentpt->left) {
                    RIGHT_ROTATE(T,&parentpt);
                    (*z) = parentpt;
                    parentpt = (*z)->parent;
                }
                LEFT_ROTATE(T,&grandparent);
                parentpt->color = BLACK;
                grandparent->color = RED;
                (*z) = parentpt;
            }
        }
    }
    (*T)->color = BLACK;
}
NODE* RB_INSERT_INDEX(NODE* T, bool enable, int index, char* title, int year, int runtime, char *genres) {
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

    while (x!=NULL) {
        y = x;
        if(z->index < x->index)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y==NULL)
        T = z;
    else if (z->index < y->index)
        y->left = z;
    else
        y->right = z;
    RB_INSERT_FIXUP(&T,&z);
    return T;
}
NODE* RB_INSERT_TITLE(NODE* T, bool enable, int index, char* title, int year, int runtime, char *genres) {
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

    while (x!=NULL) {
        y = x;
        if (strcmp(z->title,x->title) < 0)
            x = x->left;

        else
            x = x->right;
    }
    z->parent = y;
    if (y==NULL)
        T = z;
    else if (strcmp(z->title, y->title) < 0)
        y->left = z;
    else
        y->right = z;
    RB_INSERT_FIXUP(&T,&z);
    return T;
}
NODE* RB_INSERT_YEAR(NODE* T, bool enable, int index, char* title, int year, int runtime, char *genres) {
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

    while (x!=NULL) {
        y = x;
        if(z->year < x->year)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y==NULL)
        T = z;
    else if (z->year < y->year)
        y->left = z;
    else
        y->right = z;
    RB_INSERT_FIXUP(&T,&z);
    return T;
}
NODE* RB_INSERT_RUNTIME(NODE* T, bool enable, int index, char* title, int year, int runtime, char *genres) {
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

    while (x!=NULL) {
        y = x;
        if(z->runtime < x->runtime)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y==NULL)
        T = z;
    else if (z->runtime < y->runtime)
        y->left = z;
    else
        y->right = z;
    RB_INSERT_FIXUP(&T,&z);
    return T;
}

// DELETE
void RB_TRANSPLANT(NODE** T, NODE** u, NODE** v) {
    if ((*u)->parent == NULL)
        *T = *v;
    else if ((*u)==(*u)->parent->left)
        (*u)->parent->left = *v;
    else (*u)->parent->right = *v;
    if ((*v)!=NULL) 
        (*v)->parent = (*u)->parent;
}
void RB_DELETE_FIXUP(NODE** T, NODE** x) {
    while((*x)!=*T && (*x)->color == BLACK) {
        if((*x)==(*x)->parent->left) {
            NODE* w = (*x)->parent->right;
            if (w->color==RED) {
                w->color = BLACK;
                (*x)->parent->color = BLACK;
                LEFT_ROTATE(T,&((*x)->parent));
                w = (*x)->parent->right;
            }
            if (w->left->color==BLACK && w->right->color == BLACK) {
                w->color = RED;
                (*x) = (*x)->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    RIGHT_ROTATE(T,&w);
                    w = (*x)->parent->right;
                }
                w->color = (*x)->parent->color;
                (*x)->parent->color = BLACK;
                w->right->color = BLACK;
                LEFT_ROTATE(T,&((*x)->parent));
                (*x) = *T;
            }
        } else {
            NODE* w = (*x)->parent->left;
            if (w->color==RED) {
                w->color = BLACK;
                (*x)->parent->color = BLACK;
                RIGHT_ROTATE(T,&((*x)->parent));
                w = (*x)->parent->left;
            }
            if (w->right->color==BLACK && w->left->color == BLACK) {
                w->color = RED;
                (*x) = (*x)->parent;
            } else {
                if(w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    LEFT_ROTATE(T,&w);
                    w = (*x)->parent->left;
                }
                w->color = (*x)->parent->color;
                (*x)->parent->color = BLACK;
                w->left->color = BLACK;
                RIGHT_ROTATE(T,&((*x)->parent));
                (*x) = *T;
            }
        }
    }
    (*x)->color = BLACK;
}
NODE* RB_DELETE(NODE* T, NODE* z) {
    NODE* y = z;
    enum type y_original_color = z->color;
    NODE* x;

    if (z->left==NULL ) {
        x = z->right;
        RB_TRANSPLANT(&T,&z,&(z->right));
    } else if (z->right==NULL ) {
        x = z->left;
        RB_TRANSPLANT(&T,&z,&(z->left));
    } else {
        y = TREE_MINIMUM(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent==z)
            x->parent = y;
        else {
            RB_TRANSPLANT(&T,&y,&(y->right));
            y->right = z->right;
            y->right->parent = y;
        }
        RB_TRANSPLANT(&T,&z,&y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (y_original_color==BLACK)
        RB_DELETE_FIXUP(&T,&x);
    return T;
}

// PRINT
void INORDER_TREE_WALK(NODE* root) {
    if (root!=NULL) {
        INORDER_TREE_WALK(root->left);
        if (root->enable == 1)
            printf("%d\t%d\t%s\t%d\t%d\t%s\n", root->enable, root->index, root->title, root->year, root->runtime, root->genres);
        INORDER_TREE_WALK(root->right);
    }
}
void OUTORDER_TREE_WALK(NODE* root) {
    if (root!=NULL) {
        OUTORDER_TREE_WALK(root->right);
        printf("%d\t%d\t%s\t%d\t%d\t%s\n", root->enable, root->index, root->title, root->year, root->runtime, root->genres);
        OUTORDER_TREE_WALK(root->left);
    }
}
void INORDER_TREE_WALK_DELETED(NODE* root) {
    if (root!=NULL) {
        INORDER_TREE_WALK_DELETED(root->left);
        if (root->enable == 0)
            printf("%d\t%d\t%s\t%d\t%d\t%s\n", root->enable, root->index, root->title, root->year, root->runtime, root->genres);
        INORDER_TREE_WALK_DELETED(root->right);
    }
}
void INORDER_TREE_WALK_YEAR_BIGGER(NODE* root, int year) {
    if (root!=NULL) {
        INORDER_TREE_WALK_YEAR_BIGGER(root->left, year);
        if (root->year > year)
            printf("%d\t%d\t%s\t%d\t%d\t%s\n", root->enable, root->index, root->title, root->year, root->runtime, root->genres);
        INORDER_TREE_WALK_YEAR_BIGGER(root->right, year);
    }
}
void INORDER_TREE_WALK_YEAR_SMALLER(NODE* root, int year) {
    if (root!=NULL) {
        INORDER_TREE_WALK_YEAR_SMALLER(root->left, year);
        if (root->year < year)
            printf("%d\t%d\t%s\t%d\t%d\t%s\n", root->enable, root->index, root->title, root->year, root->runtime, root->genres);
        INORDER_TREE_WALK_YEAR_SMALLER(root->right, year);
    }
}
void INORDER_TREE_WALK_RUNTIME_BIGGER(NODE* root, int runtime) {
    if (root!=NULL) {
        INORDER_TREE_WALK_RUNTIME_BIGGER(root->left, runtime);
        if (root->runtime > runtime)
            printf("%d\t%d\t%s\t%d\t%d\t%s\n", root->enable, root->index, root->title, root->year, root->runtime, root->genres);
        INORDER_TREE_WALK_RUNTIME_BIGGER(root->right, runtime);
    }
}
void INORDER_TREE_WALK_RUNTIME_SMALLER(NODE* root, int runtime) {
    if (root!=NULL) {
        INORDER_TREE_WALK_RUNTIME_SMALLER(root->left, runtime);
        if (root->runtime < runtime)
            printf("%d\t%d\t%s\t%d\t%d\t%s\n", root->enable, root->index, root->title, root->year, root->runtime, root->genres);
        INORDER_TREE_WALK_RUNTIME_SMALLER(root->right, runtime);
    }
}
void INORDER_TREE_WALK_GENRES(NODE* root, char* genres) {
     if (root!=NULL) {
        INORDER_TREE_WALK_GENRES(root->left, genres);
        if (strstr(root->genres,genres) != NULL)
            printf("%d\t%d\t%s\t%d\t%d\t%s\n", root->enable, root->index, root->title, root->year, root->runtime, root->genres);
        INORDER_TREE_WALK_GENRES(root->right, genres);
     }
}

// SEARCH
NODE* TREE_SEARCH_INDEX(NODE* root, int x) {
    if (root==NULL || root->index == x)
        return root;
    else if (x < root->index)
       return  TREE_SEARCH_INDEX(root->left,x);
    else return TREE_SEARCH_INDEX(root->right,x);
}
NODE* TREE_SEARCH_TITLE(NODE* root, char* str) {
    if (root==NULL || strcmp(root->title,str)==0)
        return root;
    else if (strcmp(root->title, str) > 0)
        return  TREE_SEARCH_TITLE(root->left,str);
    else return TREE_SEARCH_TITLE(root->right,str);
}

// MODIFY
void RBT_MODIFY(NODE* root, bool enable, char* index, char* title, char* year, char* runtime, char* genres) {
    root->enable = enable;
    if (strcmp(index, "")!=0)
        root->index = atoi(index);
    if (strcmp(title, "")!=0)
        root->title = title;
    if (strcmp(year, "")!=0)
        root->year = atoi(year);
    if (strcmp(runtime, "")!=0)
        root->runtime = atoi(runtime);
    if (strcmp(genres, "")!=0)
        root->genres = genres;
}

// RBT to RBT
void RBT_EXPORT_TITLE(NODE* root, NODE** RBT_title)  {
    if (root==NULL)
        return;
    RBT_EXPORT_TITLE(root->left, RBT_title);
    *RBT_title = RB_INSERT_TITLE(*RBT_title, root->enable, root->index, root->title, root->year, root->runtime, root->genres);
	RBT_EXPORT_TITLE(root->right, RBT_title);
}
void RBT_EXPORT_YEAR(NODE* root, NODE** RBT_year)  {
    if (root==NULL)
        return;
    RBT_EXPORT_YEAR(root->left, RBT_year);
    *RBT_year = RB_INSERT_YEAR(*RBT_year, root->enable, root->index, root->title, root->year, root->runtime, root->genres);
	RBT_EXPORT_YEAR(root->right, RBT_year);
}
void RBT_EXPORT_RUNTIME(NODE* root, NODE** RBT_runtime)  {
    if (root==NULL)
        return;
    RBT_EXPORT_RUNTIME(root->left, RBT_runtime);
    *RBT_runtime = RB_INSERT_RUNTIME(*RBT_runtime, root->enable, root->index, root->title, root->year, root->runtime, root->genres);
	RBT_EXPORT_RUNTIME(root->right, RBT_runtime);
}

// TEMP
void RBT_PRINT_NODE(NODE* root) {
    if (root != NULL)
	    printf("%d\t%d\t%s\t%d\t%d\t%s\n\n", root->enable, root->index, root->title, root->year, root->runtime, root->genres);
}
