#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"
#include "bst.h"

void parseFILE(char *tsvfile, NODE **bst_index, NODE **bst_title, NODE **bst_startYear, NODE **bst_endYear, NODE **bst_runtime) {

	FILE *fp;
	fp = fopen(tsvfile, "r");

	if (fp == 0) {
		printf("Error\n");
		return;
	} else {
		char line[300];
		int row=0, col=0;
		while (fgets(line, 300, fp) && row<11) {
			if (row == 0) {
				row++;
				continue;
			}
			strtok(line, "\n");
			char *ptr = strdup(line);
			char *word;
			char *index, *type, *title, *adult, *startYear, *endYear, *runtime, *genres;

			while ((word = strsep(&ptr, "\t"))) {
				switch(col) {
					case 0: // index
						word[0]='0';
						word[1]='0';
						index = word;
						break;

					case 1: // type
						type = word;
						break;

					case 2: // title
						title = word;
						break;

					case 3: // title 2
						break;

					case 4: // is adult
						adult = word;
						break;

					case 5: // start year
						startYear = word;
						break;

					case 6: // end year
						endYear = word;
						break;

					case 7: // runtime
						runtime = word;
						break;

					case 8: // genres
						genres = word;
						break;
					
					default:
						break;
				}

				if (strcmp(word, "\0") == 0) {
					break;
				} else {
				}
				col++;
			}
			
			*bst_index = insert(1, *bst_index, atoi(index), type, title, adult, startYear, endYear, runtime, genres);
			*bst_title = insert(3, *bst_title, atoi(index), type, title, adult, startYear, endYear, runtime, genres);
			*bst_startYear = insert(6, *bst_index, atoi(index), type, title, adult, startYear, endYear, runtime, genres);
			*bst_endYear = insert(7, *bst_title, atoi(index), type, title, adult, startYear, endYear, runtime, genres);
			*bst_runtime = insert(8, *bst_title, atoi(index), type, title, adult, startYear, endYear, runtime, genres);
			row++;col=0;
		}
	}
}