#include <stdio.h>
#include <stdlib.h>
#include "movie.h"
#include "parse.h"
#include "bst.h"

int main(void) {

    /*
    MOVIE *movie1 = newMOVIE("Elf", 001);
    MOVIE *movie2 = newMOVIE("Hocus Pocus", 002);
    MOVIE *movie3 = newMOVIE("Christmas Vacation", 003);

    printf("%s\n", getMOVIE(movie1));
    printf("%s\n", getMOVIE(movie2));
    printf("%s\n", getMOVIE(movie3));

    freeMOVIE(movie1);
    freeMOVIE(movie2);
    freeMOVIE(movie3);
    */

    printf("name.basics.tsv\n");
    parseFILE("./data/name.basics.tsv");

    printf("title.akas.tsv\n");
    parseFILE("./data/title.akas.tsv");

    printf("title.basics.tsv\n");
    parseFILE("./data/title.basics.tsv");

    printf("title.crew.tsv\n");
    parseFILE("./data/title.crew.tsv");

    printf("title.episode.tsv\n");
    parseFILE("./data/title.episode.tsv");

    printf("title.principals.tsv\n");
    parseFILE("./data/title.principals.tsv");

    printf("title.ratings.tsv\n");
    parseFILE("./data/title.ratings.tsv");
    
    /*
    BST *bst = newBST();
    insertBST(bst, "Elf", 001);
    printf("%s", getMOVIEname(bst, "Elf"));
    */

    return 0;
}