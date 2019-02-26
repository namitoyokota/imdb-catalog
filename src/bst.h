#ifndef __BST_INCLUDED__
#define __BST_INCLUDED__

typedef struct bst BST;
typedef struct node NODE;

extern BST *newBST();
extern BST *insertBST(BST *bst, char *title, int id);
extern char *getMOVIEname(BST *bst, char *title);
extern void freeBST(BST *bst);

#endif