#ifndef rbt_h
#define rbt_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef struct node NODE;

// MAIN
void LEFT_ROTATE(NODE**, NODE**);                   // PAGE 313
void RIGHT_ROTATE(NODE**, NODE**);
NODE* TREE_MINIMUM(NODE*);                          // PAGE 291

// INSERET
void RB_INSERT_FIXUP(NODE**, NODE**);               // PAGE 316
    NODE* RB_INSERT_INDEX(NODE*, bool, int, char*, int, int, char*, char*, int, int, int);
    NODE* RB_INSERT_TITLE(NODE*, bool, int, char*, int, int, char*, char*, int, int, int);
    NODE* RB_INSERT_YEAR(NODE*, bool, int, char*, int, int, char*, char*, int, int, int);
    NODE* RB_INSERT_RUNTIME(NODE*, bool, int, char*, int, int, char*, char*, int, int, int);

// DELETE
void RB_TRANSPLANT(NODE**, NODE**, NODE**);         // PAGE 323
void RB_DELETE_FIXUP(NODE**, NODE**);               // PAGE 326
NODE* RB_DELETE(NODE*, NODE*);                      // PAGE 324

// PRINT
void INORDER_TREE_WALK(NODE*);                      // PAGE 288
void OUTORDER_TREE_WALK(NODE*);
    // DELETED List
    void INORDER_TREE_WALK_DELETED(NODE*);
    // FILTERED List
    void INORDER_TREE_WALK_YEAR_BIGGER(NODE*, int);
    void INORDER_TREE_WALK_YEAR_SMALLER(NODE*, int);
    void INORDER_TREE_WALK_RUNTIME_BIGGER(NODE*, int);
    void INORDER_TREE_WALK_RUNTIME_RUNTIME(NODE*, int);
    void INORDER_TREE_WALK_GENRES(NODE*, char*);

// SEARCH
    NODE* TREE_SEARCH_INDEX(NODE*, int);            // PAGE 290
    NODE* TREE_SEARCH_TITLE(NODE*, char*);
    void TREE_SEARCH_LIST_INDEX(NODE*, NODE**, int);
    void TREE_SEARCH_LIST_TITLE(NODE*, NODE**, char*);

// UPDATE
void RBT_MODIFY(NODE*, bool, char*, char*, char*, char*, char*, char*, int, int, int);

// RBT to RBT
    void RBT_EXPORT_TITLE(NODE*, NODE**);
    void RBT_EXPORT_YEAR(NODE*, NODE**);
    void RBT_EXPORT_RUNTIME(NODE*, NODE**);

// TEMP
void RBT_PRINT_NODE(NODE*);

#endif
