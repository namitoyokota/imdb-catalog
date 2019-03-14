#include <stdio.h>
#include <string.h>
#include "rbt.h"

void createData(NODE** root, char* index, char* title, char* year, char* runtime, char* genres) {

    *root = RB_insert(*root, '1', atoi(index), title, atoi(year), atoi(runtime), genres);

    return;
}

void retrieveData(NODE** root, char* index) {

    NODE* search = NULL;
    search = BST_search(*root, atoi(index));

    if (search == NULL) {
        printf("Error. A movie with the inputted index does not exist");
        return;
    } else {
        update_enable(search, 1);
        return;
    }
}

void updateData(NODE** root, char* index, char* title, char* year, char* runtime, char* genres) {

    NODE* search = NULL;
    search = BST_search(*root, atoi(index));

    if (search == NULL) {
        printf("Error. A movie with the inputted index does not exist\n\n");
        return;
    } else {
        if (strcmp(title, "") != 0)
            update_title(search, title);
        if (strcmp(year, "") != 0)
            update_year(search, atoi(year));
        if (strcmp(runtime, "") != 0)
            update_runtime(search, atoi(runtime));
        if (strcmp(genres, "") != 0)
            update_genres(search, genres);
        return;
    }
}

void deleteData(NODE** root, char* index) {

    NODE* search = NULL;
    search = BST_search(*root, atoi(index));

    if (search == NULL) {
        printf("Error. A movie with the inputted index does not exist\n\n");
        return;
    } else {
        update_enable(search, 0);
        return;
    }
}