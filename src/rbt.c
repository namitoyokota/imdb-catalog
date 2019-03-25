#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/rbt.h"
#include "../lib/stack.h"

enum boo {T,F};
enum type {RED,BLACK};

struct rbt {
    enum type color;
    RBT* left;
    RBT* right;
    RBT* parent;

    enum boo enable;
    int index;
    char* title;
    int year;
    int runtime;
    char* genres;
    char* media;
    int m;
    int d;
    int y;
};

// MAIN
void LEFT_ROTATE(RBT** T,RBT** X) {
    RBT* Y = (*X)->right;
    (*X)->right = Y->left;
    if (Y->left != NULL)
        Y->left->parent = *X;
    Y->parent = (*X)->parent;
    if ((*X)->parent == NULL)
        *T = Y;
    else if(*X == (*X)->parent->left)
        (*X)->parent->left = Y;
    else (*X)->parent->right = Y;
    Y->left = *X;
    (*X)->parent = Y;
}
void RIGHT_ROTATE(RBT** T,RBT** X) {
    RBT* Y = (*X)->left;
    (*X)->left = Y->right;
    if (Y->right != NULL)
        Y->right->parent = *X;
    Y->parent = (*X)->parent;
    if ((*X)->parent==NULL)
        *T = Y;
    else if ((*X)== (*X)->parent->left)
        (*X)->parent->left = Y;
    else (*X)->parent->right = Y;
    Y->right = *X;
    (*X)->parent = Y;
}
RBT* TREE_MINIMUM(RBT* rbt) {
    while (rbt->left != NULL)
        rbt = rbt->left;
    return rbt;
}

// INSERT
void RB_INSERT_FIXUP(RBT** T, RBT** Z) {
    RBT* grandparent = NULL;
    RBT* parentpt = NULL;
    while (((*Z)!=*T) && ((*Z)->color!= BLACK) && ((*Z)->parent->color == RED)) {
        parentpt = (*Z)->parent;
        grandparent = (*Z)->parent->parent;
        if (parentpt == grandparent->left) {
            RBT* uncle = grandparent->right;
            if (uncle!=NULL && uncle->color == RED) {
                grandparent->color = RED;
                parentpt->color = BLACK;
                uncle->color = BLACK;
                *Z = grandparent;
            } else {
                if ((*Z) == parentpt->right) {
                    LEFT_ROTATE(T,&parentpt);
                    (*Z) = parentpt;
                    parentpt = (*Z)->parent;
                }
                RIGHT_ROTATE(T,&grandparent);
                parentpt->color = BLACK;
                grandparent->color = RED;
                (*Z) = parentpt;
            }
        } else {
            RBT* uncle = grandparent->left;
            if (uncle!=NULL && uncle->color == RED) {
                grandparent->color = RED;
                parentpt->color = BLACK;
                uncle->color = BLACK;
                (*Z) = grandparent;
            } else {
                if ((*Z) == parentpt->left) {
                    RIGHT_ROTATE(T,&parentpt);
                    (*Z) = parentpt;
                    parentpt = (*Z)->parent;
                }
                LEFT_ROTATE(T,&grandparent);
                parentpt->color = BLACK;
                grandparent->color = RED;
                (*Z) = parentpt;
            }
        }
    }
    (*T)->color = BLACK;
}
RBT* RB_INSERT_INDEX(RBT* T, bool enable, int index, char* title, int year, int runtime, char *genres, char* media, int m, int d, int y) {
    RBT* Z = (RBT*)malloc(sizeof(struct rbt));
    Z->enable = enable;
    Z->index = index;
    Z->title = title;
    Z->year = year;
    Z->runtime = runtime;
    Z->genres = genres;
    Z->media = media;
    Z->m = m;
    Z->d = d;
    Z->y = y;

    Z->left = NULL;
    Z->right = NULL;
    Z->parent = NULL;
    Z->color = RED;

    RBT* Y = NULL;
    RBT* X = T;

    while (X != NULL) {
        Y = X;
        if(Z->index < X->index)
            X = X->left;
        else
            X = X->right;
    }
    Z->parent = Y;
    if (Y == NULL)
        T = Z;
    else if (Z->index < Y->index)
        Y->left = Z;
    else
        Y->right = Z;
    RB_INSERT_FIXUP(&T,&Z);
    return T;
}
RBT* RB_INSERT_TITLE(RBT* T, bool enable, int index, char* title, int year, int runtime, char *genres, char* media, int m, int d, int y) {
    RBT* Z = (RBT*)malloc(sizeof(struct rbt));
    Z->enable = enable;
    Z->index = index;
    Z->title = title;
    Z->year = year;
    Z->runtime = runtime;
    Z->genres = genres;
    Z->media = media;
    Z->m = m;
    Z->d = d;
    Z->y = y;

    Z->left = NULL;
    Z->right = NULL;
    Z->parent = NULL;
    Z->color = RED;

    RBT* Y = NULL;
    RBT* X = T;

    while (X != NULL) {
        Y = X;
        if (strcmp(Z->title, X->title) < 0)
            X = X->left;
        else
            X = X->right;
    }
    Z->parent = Y;
    if (Y == NULL)
        T = Z;
    else if (strcmp(Z->title, Y->title) < 0)
        Y->left = Z;
    else
        Y->right = Z;
    RB_INSERT_FIXUP(&T,&Z);
    return T;
}
RBT* RB_INSERT_YEAR(RBT* T, bool enable, int index, char* title, int year, int runtime, char *genres, char* media, int m, int d, int y) {
    RBT* Z = (RBT*)malloc(sizeof(struct rbt));
    Z->enable = enable;
    Z->index = index;
    Z->title = title;
    Z->year = year;
    Z->runtime = runtime;
    Z->genres = genres;
    Z->media = media;
    Z->m = m;
    Z->d = d;
    Z->y = y;

    Z->left = NULL;
    Z->right = NULL;
    Z->parent = NULL;
    Z->color = RED;

    RBT* Y = NULL;
    RBT* X = T;

    while (X != NULL) {
        Y = X;
        if(Z->year < X->year)
            X = X->left;
        else
            X = X->right;
    }
    Z->parent = Y;
    if (Y == NULL)
        T = Z;
    else if (Z->year < Y->year)
        Y->left = Z;
    else
        Y->right = Z;
    RB_INSERT_FIXUP(&T,&Z);
    return T;
}
RBT* RB_INSERT_RUNTIME(RBT* T, bool enable, int index, char* title, int year, int runtime, char *genres, char* media, int m, int d, int y) {
    RBT* Z = (RBT*)malloc(sizeof(struct rbt));
    Z->enable = enable;
    Z->index = index;
    Z->title = title;
    Z->year = year;
    Z->runtime = runtime;
    Z->genres = genres;
    Z->media = media;
    Z->m = m;
    Z->d = d;
    Z->y = y;

    Z->left = NULL;
    Z->right = NULL;
    Z->parent = NULL;
    Z->color = RED;

    RBT* Y = NULL;
    RBT* X = T;

    while (X != NULL) {
        Y = X;
        if(Z->runtime < X->runtime)
            X = X->left;
        else
            X = X->right;
    }
    Z->parent = Y;
    if (Y == NULL)
        T = Z;
    else if (Z->runtime < Y->runtime)
        Y->left = Z;
    else
        Y->right = Z;
    RB_INSERT_FIXUP(&T,&Z);
    return T;
}

// DELETE
void RB_TRANSPLANT(RBT** T, RBT** U, RBT** V) {
    if ((*U)->parent == NULL)
        *T = *V;
    else if ((*U)==(*U)->parent->left)
        (*U)->parent->left = *V;
    else (*U)->parent->right = *V;
    if ((*V)!=NULL) 
        (*V)->parent = (*U)->parent;
}
void RB_DELETE_FIXUP(RBT** T, RBT** X) {
    while((*X) != *T && (*X)->color == BLACK) {
        if((*X) == (*X)->parent->left) {
            RBT* W = (*X)->parent->right;
            if (W->color == RED) {
                W->color = BLACK;
                (*X)->parent->color = BLACK;
                LEFT_ROTATE(T, &((*X)->parent));
                W = (*X)->parent->right;
            }
            if (W->left->color == BLACK && W->right->color == BLACK) {
                W->color = RED;
                (*X) = (*X)->parent;
            } else {
                if (W->right->color == BLACK) {
                    W->left->color = BLACK;
                    W->color = RED;
                    RIGHT_ROTATE(T, &W);
                    W = (*X)->parent->right;
                }
                W->color = (*X)->parent->color;
                (*X)->parent->color = BLACK;
                W->right->color = BLACK;
                LEFT_ROTATE(T, &((*X)->parent));
                (*X) = *T;
            }
        } else {
            RBT* W = (*X)->parent->left;
            if (W->color == RED) {
                W->color = BLACK;
                (*X)->parent->color = BLACK;
                RIGHT_ROTATE(T, &((*X)->parent));
                W = (*X)->parent->left;
            }
            if (W->right->color == BLACK && W->left->color == BLACK) {
                W->color = RED;
                (*X) = (*X)->parent;
            } else {
                if(W->left->color == BLACK) {
                    W->right->color = BLACK;
                    W->color = RED;
                    LEFT_ROTATE(T, &W);
                    W = (*X)->parent->left;
                }
                W->color = (*X)->parent->color;
                (*X)->parent->color = BLACK;
                W->left->color = BLACK;
                RIGHT_ROTATE(T,&((*X)->parent));
                (*X) = *T;
            }
        }
    }
    (*X)->color = BLACK;
}
RBT* RB_DELETE(RBT* T, RBT* Z) {
    RBT* Y = Z;
    enum type y_original_color = Z->color;
    RBT* X;

    if (Z->left==NULL ) {
        X = Z->right;
        RB_TRANSPLANT(&T, &Z, &(Z->right));
    } else if (Z->right==NULL ) {
        X = Z->left;
        RB_TRANSPLANT(&T, &Z, &(Z->left));
    } else {
        Y = TREE_MINIMUM(Z->right);
        y_original_color = Y->color;
        X = Y->right;
        if (Y->parent == Z)
            X->parent = Y;
        else {
            RB_TRANSPLANT(&T, &Y, &(Y->right));
            Y->right = Z->right;
            Y->right->parent = Y;
        }
        RB_TRANSPLANT(&T, &Z, &Y);
        Y->left = Z->left;
        Y->left->parent = Y;
        Y->color = Z->color;
    }
    if (y_original_color == BLACK)
        RB_DELETE_FIXUP(&T,&X);
    return T;
}

// PRINT
void INORDER_TREE_WALK(RBT* root) {
    if (root!=NULL) {
        INORDER_TREE_WALK(root->left);
        printf("%d\t%d\t%s\t%d\t%d\t%s\t%s\t%d\t%d\t%d\n", root->enable, root->index, root->title, root->year, root->runtime, root->genres, root->media, root->m, root->d, root->y);
        INORDER_TREE_WALK(root->right);
    }
}
void OUTORDER_TREE_WALK(RBT* root) {
    if (root!=NULL) {
        OUTORDER_TREE_WALK(root->right);
        printf("%d\t%d\t%s\t%d\t%d\t%s\t%s\t%d\t%d\t%d\n", root->enable, root->index, root->title, root->year, root->runtime, root->genres, root->media, root->m, root->d, root->y);
        OUTORDER_TREE_WALK(root->left);
    }
}
void INORDER_TREE_WALK_DELETED(RBT* root) {
    if (root!=NULL) {
        INORDER_TREE_WALK_DELETED(root->left);
        if (root->enable == 0)
            push(root->enable, root->index, root->title, root->year, root->runtime, root->genres, root->media, root->m, root->d, root->y);
        INORDER_TREE_WALK_DELETED(root->right);
    }
}
void INORDER_TREE_WALK_YEAR_BIGGER(RBT* root, int year) {
    if (root!=NULL) {
        INORDER_TREE_WALK_YEAR_BIGGER(root->left, year);
        if (root->year > year && root->enable == 1)
            push(root->enable, root->index, root->title, root->year, root->runtime, root->genres, root->media, root->m, root->d, root->y);
        INORDER_TREE_WALK_YEAR_BIGGER(root->right, year);
    }
}
void INORDER_TREE_WALK_YEAR_SMALLER(RBT* root, int year) {
    if (root!=NULL) {
        INORDER_TREE_WALK_YEAR_SMALLER(root->left, year);
        if (root->year < year && root->enable == 1)
            push(root->enable, root->index, root->title, root->year, root->runtime, root->genres, root->media, root->m, root->d, root->y);
        INORDER_TREE_WALK_YEAR_SMALLER(root->right, year);
    }
}
void INORDER_TREE_WALK_RUNTIME_BIGGER(RBT* root, int runtime) {
    if (root!=NULL) {
        INORDER_TREE_WALK_RUNTIME_BIGGER(root->left, runtime);
        if (root->runtime > runtime && root->enable == 1)
            push(root->enable, root->index, root->title, root->year, root->runtime, root->genres, root->media, root->m, root->d, root->y);
        INORDER_TREE_WALK_RUNTIME_BIGGER(root->right, runtime);
    }
}
void INORDER_TREE_WALK_RUNTIME_SMALLER(RBT* root, int runtime) {
    if (root!=NULL) {
        INORDER_TREE_WALK_RUNTIME_SMALLER(root->left, runtime);
        if (root->runtime < runtime && root->enable == 1)
            push(root->enable, root->index, root->title, root->year, root->runtime, root->genres, root->media, root->m, root->d, root->y);
        INORDER_TREE_WALK_RUNTIME_SMALLER(root->right, runtime);
    }
}

// SEARCH
RBT* TREE_SEARCH_INDEX(RBT* root, int X) {
    if (root == NULL || root->index == X)
        return root;
    else if (X < root->index)
       return  TREE_SEARCH_INDEX(root->left, X);
    else return TREE_SEARCH_INDEX(root->right, X);
}
RBT* TREE_SEARCH_TITLE(RBT* root, char* str) {
    if (root == NULL || strcasestr(root->title,str) != 0)
        return root;
    else if (strcasestr(root->title, str) > 0)
        return  TREE_SEARCH_TITLE(root->left,str);
    else return TREE_SEARCH_TITLE(root->right,str);
}
void TREE_SEARCH_LIST_INDEX(RBT* root, int X) {
    if (root->index == X && root->enable == 1) {
        push(root->enable, root->index, root->title, root->year, root->runtime, root->genres, root->media, root->m, root->d, root->y);
    }
    if (root->left != NULL) 
        TREE_SEARCH_LIST_INDEX(root->left, X);
    if (root->right != NULL)
        TREE_SEARCH_LIST_INDEX(root->right, X);
}
void TREE_SEARCH_LIST_TITLE(RBT* root, char* str) {
    if (strcasestr(root->title, str) != 0 && root->enable == 1) {
        push(root->enable, root->index, root->title, root->year, root->runtime, root->genres, root->media, root->m, root->d, root->y);
    }
    if (root->left != NULL) 
        TREE_SEARCH_LIST_TITLE(root->left, str);
    if (root->right != NULL)
        TREE_SEARCH_LIST_TITLE(root->right, str);
}
void TREE_SEARCH_LIST_GENRE(RBT* root, char* str) {
    if (strcasestr(root->genres, str) != 0 && root->enable == 1) {
        push(root->enable, root->index, root->title, root->year, root->runtime, root->genres, root->media, root->m, root->d, root->y);
    }
    if (root->left != NULL) 
        TREE_SEARCH_LIST_GENRE(root->left, str);
    if (root->right != NULL)
        TREE_SEARCH_LIST_GENRE(root->right, str);
}

// MODIFY
void RBT_MODIFY(RBT* root, bool enable, char* index, char* title, char* year, char* runtime, char* genres, char* media, int m, int d, int y) {
    root->enable = enable;
    if (strcmp(index, "") != 0)
        root->index = atoi(index);
    if (strcmp(title, "") != 0)
        root->title = title;
    if (strcmp(year, "") != 0)
        root->year = atoi(year);
    if (strcmp(runtime, "") != 0)
        root->runtime = atoi(runtime);
    if (strcmp(genres, "") != 0)
        root->genres = genres;
    if (strcmp(media, "") != 0)
        root->media = media;
    if (m != 0)
        root->m = m;
    if (d != 0) 
        root->d = d;
    if (y != 0)
        root->y = y;
}

// RBT to RBT
void RBT_EXPORT_TITLE(RBT* root, RBT** RBT_title)  {
    if (root==NULL)
        return;
    RBT_EXPORT_TITLE(root->left, RBT_title);
    *RBT_title = RB_INSERT_TITLE(*RBT_title, root->enable, root->index, root->title, root->year, root->runtime, root->genres, root->media, root->m, root->d, root->y);
	RBT_EXPORT_TITLE(root->right, RBT_title);
}
void RBT_EXPORT_YEAR(RBT* root, RBT** RBT_year)  {
    if (root==NULL)
        return;
    RBT_EXPORT_YEAR(root->left, RBT_year);
    *RBT_year = RB_INSERT_YEAR(*RBT_year, root->enable, root->index, root->title, root->year, root->runtime, root->genres, root->media, root->m, root->d, root->y);
	RBT_EXPORT_YEAR(root->right, RBT_year);
}
void RBT_EXPORT_RUNTIME(RBT* root, RBT** RBT_runtime)  {
    if (root==NULL)
        return;
    RBT_EXPORT_RUNTIME(root->left, RBT_runtime);
    *RBT_runtime = RB_INSERT_RUNTIME(*RBT_runtime, root->enable, root->index, root->title, root->year, root->runtime, root->genres, root->media, root->m, root->d, root->y);
	RBT_EXPORT_RUNTIME(root->right, RBT_runtime);
}

void INORDER_STACK(RBT* root, STACK* s) {
    if (root!=NULL) {
        INORDER_STACK(root->right, s);
        if (root->enable == 1)
            push(root->enable, root->index, root->title, root->year, root->runtime, root->genres, root->media, root->m, root->d, root->y);
        INORDER_STACK(root->left, s);
    }
}

void OUTORDER_STACK(RBT* root, STACK* s) {
    if (root!=NULL) {
        OUTORDER_STACK(root->left, s);
        if (root->enable != 0)
            push(root->enable, root->index, root->title, root->year, root->runtime, root->genres, root->media, root->m, root->d, root->y);
        OUTORDER_STACK(root->right, s);
    }
}