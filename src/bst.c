#include <stdlib.h>
#include "bst.h"
#include "movie.h"

struct node {
    MOVIE *movie;
    NODE *left;
    NODE *right;
};

struct bst {
    NODE *root;
};

NODE *newNODE(char *title, int id) {
    NODE *node = malloc(sizeof(NODE));
    node->movie = newMOVIE(title, id);
    node->left = NULL;
    node->right = NULL;
    return node;
}

BST *newBST() {
    BST *bst = malloc(sizeof(BST));
    bst->root = NULL;
    return  bst;
}

BST *insertBST(BST *bst, char *title, int id) {
    NODE *node = newNODE(title, id);

    if (bst->root == NULL) {
        // if the root node is empty insert at the top
        bst->root = node;
    } else {
        // go through the tree then insert
    }

    return bst;
}

char *getMOVIEname(BST *bst, char *title) {
    // go through tree and find movie
    //if (strcmp(bst->root->movie->getMOVIE(), title) == 0)
        //return bst->root->movie.getMOVIE();
}

/*
MOVIE *getMOVIE(BST *bst, int id) {
    // go through tree and find movie
    return
}
*/

void freeBST(BST *bst) {
    free(bst);
}