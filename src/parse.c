#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"
#include "rbt.h"

void parseFILE(char *tsvfile, NODE** RBT) {
	FILE *fp;
	fp = fopen(tsvfile, "r");

	if (fp == 0) {
		printf("Error\n");
		return;
	} else {
		char line[300];
		int row=0, col=0;
		while (fgets(line, 300, fp) && row < 15) {
			if (row == 0) {
				row++;
				continue;
			}
			strtok(line, "\n");
			char *ptr = strdup(line);
			char *word;
			char *index, *title, *adult, *year, *runtime, *genres;

			while ((word = strsep(&ptr, "\t"))) {
				switch(col) {
					case 0: // index
						word[0]='0';
						word[1]='0';
						index = word;
						break;

					case 1: // type
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
						year = word;
						break;

					case 6: // end year
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

			*RBT = RB_insert(*RBT, '0', atoi(index), title, atoi(year), atoi(runtime), genres);

			printf("%s\n",index);
			row++;col=0;
		}
	}
}