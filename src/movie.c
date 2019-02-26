#include <stdio.h>
#include <stdlib.h>
#include "movie.h"

struct movie
{
    char *title;
    int id;
};

extern MOVIE *newMOVIE(char *title, int id) {
    MOVIE *m = malloc(sizeof(MOVIE));
    m->title = title;
    m->id = id;
    return m;
}

extern char *getMOVIE(MOVIE *m) {
    return m->title;
}

extern void setMOVIE(MOVIE *m, char *title, int id) {
    m->title = title;
    m->id = id;
}

extern void freeMOVIE(void *m) {
    free((MOVIE *) m);
}