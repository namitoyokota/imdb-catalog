#include <stdio.h>
#include <string.h>
#include "../lib/rbt.h"
#include "../lib/logger.h"

void CREATE_MOVIE(char* filename, NODE** root, char* index, char* title, char* year, char* runtime, char* genres, char* media, char* m, char* d, char* y) {
    *root = RB_INSERT_INDEX(*root, 1, atoi(index), title, atoi(year), atoi(runtime), genres, media, atoi(m), atoi(d), atoi(y));
    if (strcmp(filename, "./logs/") != 0) {
        char message[100] = "Create,"; strcat(message, index); strcat(message, ","); strcat(message, title); strcat(message, ",");
            strcat(message, year); strcat(message, ","); strcat(message, runtime); strcat(message, ","); strcat(message, genres); strcat(message, ","); 
            strcat(message, media); strcat(message, ","); strcat(message, m); strcat(message, ","); strcat(message, d); strcat(message, ",");
            strcat(message, y);
        printLog(filename, message);
    }
}

void RETRIEVE_MOVIE(char* filename, NODE** root, char* index) {
    NODE* search = TREE_SEARCH_INDEX(*root, atoi(index));
    if (search == NULL) printf("Error. A movie with the inputted index does not exist");
    else RBT_MODIFY(search, 1, "", "", "", "", "", "", 0,0,0);
    if (strcmp(filename, "./logs/") != 0) {
        char message[100] = "Retrieve,"; strcat(message, index);
        printLog(filename, message);
    }
}

void UPDATE_MOVIE(char* filename, NODE** root, char* index, char* title, char* year, char* runtime, char* genres, char* media, char* m, char* d, char* y) {
    NODE* search = TREE_SEARCH_INDEX(*root, atoi(index));
    if (search == NULL)  {
        printf("Error. A movie with the inputted index does not exist\n\n");
    } else {
        RBT_MODIFY(search, 1, index, title, year, runtime, genres, media, atoi(m), atoi(d), atoi(y));
        // if index is ever changed, the node should be deleted then inserted again to sort in the right location
        //*root = RB_DELETE(*root, search);
        //*root = RB_INSERT_INDEX(*root, 1, atoi(index), title, atoi(year), atoi(runtime), genres);
    }
    if (strcmp(filename, "./logs/") != 0) {
        char message[100] = "Update,"; strcat(message, index); strcat(message, ","); strcat(message, title); strcat(message, ",");
            strcat(message, year); strcat(message, ","); strcat(message, runtime); strcat(message, ","); strcat(message, genres); strcat(message, ","); 
            strcat(message, media); strcat(message, ","); strcat(message, m); strcat(message, ","); strcat(message, d); strcat(message, ",");
            strcat(message, y);
        printLog(filename, message);
    }
}

void DELETE_MOVIE(char* filename, NODE** root, char* index) {
    NODE* search = NULL;
    search = TREE_SEARCH_INDEX(*root, atoi(index));
    if (search == NULL) printf("Error. A movie with the inputted index does not exist\n\n");
    else RBT_MODIFY(search, 0, "", "", "", "", "", "", 0,0,0);
    if (strcmp(filename, "./logs/") != 0) {
        char message[100] = "Delete,"; strcat(message, index);
        printLog(filename, message);
    }
}