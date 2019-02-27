#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"
#include "bst.h"

NODE* parseFILE(char *tsvfile, NODE *bst) {

	FILE *fp;
	fp = fopen(tsvfile, "r");

	if (fp == 0) {
		printf("Error\n");
		return bst;
	} else {
		char line[300];
		int row=0, col=0;
		while (fgets(line, 300, fp) && row<10) {
			strtok(line, "\n");
			char *ptr = strdup(line);
			char *word;
			char *index, *type, *title, *genres;

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
						break;
					case 5: // start year
						break;
					case 6: // end year
						break;
					case 7: // runtime
						break;
					case 8: // genres
						genres = word;
						break;
				}

				if (strcmp(word, "\0") == 0) {
					break;
				} else {
					printf("%s\t", word);
				}
				col++;
			}
			bst = insert(bst, atoi(index), title, type, genres);
			printf("\n");
			row++;col=0;
		}
	}

	return bst;
}