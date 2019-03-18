#include "../lib/logger.h"
#include <stdio.h>
#include "../lib/rbt.h"
#include "../lib/crud.h"

void printLog(char* filename, char* message) {
    printf("printLog\n");
    FILE* fp = fopen(filename, "ab+");
    if (fp != 0) {
        fprintf(fp, "%s\n", message);
        fclose(fp);
    }
}

void readLog(char* filename, NODE** root) {
    printf("readLog\n");
    FILE* fp = fopen(filename, "r");
    if (fp == 0) {
        // file not found
    } else {
        // file found
        char line[100]; int row=0, col=0;
		while (fgets(line, 100, fp)) {
			strtok(line, "\n"); char *ptr = strdup(line), *word, *function, *index, *title, *year, *runtime, *genres, *media, *m, *d, *y;
			while ((word = strsep(&ptr, ","))) {
				switch(col) {
                    case 0: function = word; break;
                    case 1: index = word; break;
                    case 2: title = word; break;
                    case 3: year = word; break;
                    case 4: runtime = word; break;
                    case 5: genres = word; break;
                    case 6: media = word; break;
                    case 7: m = word; break;
                    case 8: d = word; break;
                    case 9: y = word; break;
					default: break;
				}
				if (strcmp(word, "\0") == 0) break;
				col++;
			}
            printf("function: %s\n", function);
            if (strcmp(function, "Create") == 0) {
                CREATE_MOVIE("", root, index, title, year, runtime, genres, media, m, d, y);
            } else if (strcmp(function, "Retreive") == 0) {
                RETRIEVE_MOVIE("", root, index);
            } else if (strcmp(function, "Update") == 0) {
                UPDATE_MOVIE("", root, index, title, year, runtime, genres, media, m, d, y);
            } else if (strcmp(function, "Delete") == 0) {
                DELETE_MOVIE("", root, index);
            } else {
                printf("the function does not exist");
            }
			row++; col=0;
		}
    }
    fclose(fp);
}