#ifndef movie_h
#define movie_h

#include <stdio.h>

typedef struct movie MOVIE;

extern MOVIE *newMOVIE(char *title, int id);
extern char* getMOVIE(MOVIE *);
extern void setMOVIE(MOVIE *, char *, int);
extern void freeMOVIE(void *);

#endif
