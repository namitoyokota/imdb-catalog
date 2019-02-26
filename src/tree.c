#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "movie.h"

struct TREE
{
    TREE *LEFT;
    TREE *RIGHT;
    MOVIE *MOVIE;
};

extern TREE *newTREE(char *title, int id) {
    TREE *t = malloc(sizeof(TREE));
    return t;
}