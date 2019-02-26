#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"

void parseFILE(char *tsvfile) {

	FILE *fp;
	fp = fopen(tsvfile, "r");

	if (fp == 0) {
		printf("Error\n");
		return;
	} else {
		char line[300];
		int count=0;
		while (fgets(line, 300, fp) && count<10) {
			strtok(line, "\n");
			char *ptr = strdup(line);
			char *word;

			while ((word = strsep(&ptr, "\t"))) {
				if (strcmp(word, "\0") == 0) {
					break;
				} else {
					printf("%s\t", word);
				}
			}
			printf("endl\n");
			count++;
		}
	}
}