#include <stdio.h>
#include <string.h>
#include "rbt.h"

void CREATE_MOVIE(NODE** root, char* index, char* title, char* year, char* runtime, char* genres) {
    *root = RB_INSERT_INDEX(*root, 1, atoi(index), title, atoi(year), atoi(runtime), genres);
}

void RETRIEVE_MOVIE(NODE** root, char* index) {
    NODE* search = TREE_SEARCH_INDEX(*root, atoi(index));
    if (search == NULL) printf("Error. A movie with the inputted index does not exist");
    else RBT_MODIFY(search, 1, "", "", "", "", "");
}

void UPDATE_MOVIE(NODE** root, char* index, char* title, char* year, char* runtime, char* genres) {
    NODE* search = TREE_SEARCH_INDEX(*root, atoi(index));
    if (search == NULL)  {
        printf("Error. A movie with the inputted index does not exist\n\n");
    } else {
        RBT_MODIFY(search, 1, index, title, year, runtime, genres);
        // if index is ever changed, the node should be deleted then inserted again to sort in the right location
        //*root = RB_DELETE(*root, search);
        //*root = RB_INSERT_INDEX(*root, 1, atoi(index), title, atoi(year), atoi(runtime), genres);
    }
}

void DELETE_MOVIE(NODE** root, char* index) {
    NODE* search = NULL;
    search = TREE_SEARCH_INDEX(*root, atoi(index));
    if (search == NULL) printf("Error. A movie with the inputted index does not exist\n\n");
    else RBT_MODIFY(search, 0, "", "", "", "", "");
}