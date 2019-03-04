#include <stdio.h>
#include <stdlib.h>
#include "parse.h"
#include "bst.h"

int main(void) {

	// sort
    NODE *sort_index=NULL, *sort_title=NULL, *sort_startYear=NULL, *sort_endYear=NULL, *sort_runtime=NULL;

	/*
	// filter
	NODE *filter_adult=NULL;

	// filter_type
	NODE *filter_short=NULL, *filter_tvepisode=NULL, *filter_tvseries=NULL, *filter_tvmovie=NULL, *filter_movie=NULL, *filter_video=NULL;

	// filter_genres
	NODE *filter_Short=NULL, *filter_comedy=NULL, *filter_drama=NULL, *filter_romance=NULL, *filter_adventure=NULL, *filter_animation=NULL, *filter_documentary=NULL,
		*filter_talkshow=NULL, *filter_fantasy=NULL, *filter_scifi=NULL, *filter_gameshow=NULL, *filter_realitytv=NULL, *filter_horror=NULL,
		*filter_thriller=NULL, *filter_action=NULL, *filter_crime=NULL, *filter_mystery=NULL, *filter_news=NULL, *filter_family=NULL, *filter_sport=NULL,
		*filter_music=NULL, *filter_biography=NULL;
	*/

    parseFILE("./data/title.basics.tsv", &sort_index, &sort_title, &sort_startYear, &sort_endYear, &sort_runtime);

	while(1) {
		int menu;
		printf(" ___________________________________________\n");
		printf("|                                           |\n");
		printf("|                  MENU                     |\n");
		printf("|   1. PRINT INDEX IN INCREASING ORDER      |\n");
		printf("|   2. PRINT INDEX IN DECREASING ORDER      |\n");
		printf("|   3. PRINT TITLE IN INCREASING ORDER      |\n");
		printf("|   4. PRINT TITLE IN DECREASING ORDER      |\n");
		printf("|   5. PRINT STARTYEAR IN INCREASING ORDER  |\n");
		printf("|   6. PRINT STARTYEAR IN DECREASING ORDER  |\n");
		printf("|   7. PRINT ENDYEAR IN INCREASING ORDER    |\n");
		printf("|   8. PRINT ENDYEAR IN DECREASING ORDER    |\n");
		printf("|   9. PRINT RUNTIME IN INCREASING ORDER    |\n");
		printf("|   10. PRINT RUNTIME IN DECREASING ORDER   |\n");
		printf("|   11. HELP                                |\n");
		printf("|   12. QUIT                                |\n");
		printf("|___________________________________________|\n");
		printf("\n\tChoice : ");
		scanf("%d", &menu);

		if (menu == 11) break;
		if (menu == 12) break;

		switch(menu) {
			case 1:
				printf("\n\nIndex Increasing\n");
				printf("enable \t index \t type \t title \t adult \t start year \t end year \t runtime \t genres");
				InOrder(sort_index);
				break;

			case 2:
				printf("\n\nIndex Decreasing\n");
				printf("enable \t index \t type \t title \t adult \t start year \t end year \t runtime \t genres");
				NotOrder(sort_index);
				break;

			case 3:
				printf("\n\nTitle Increasing\n");
				printf("enable \t index \t type \t title \t adult \t start year \t end year \t runtime \t genres");
				InOrder(sort_title);
				break;

			case 4:
				printf("\n\nTitle Decreasing\n");
				printf("enable \t index \t type \t title \t adult \t start year \t end year \t runtime \t genres");
				NotOrder(sort_title);
				break;
			
			case 5:
				printf("\n\nStartYear Increasing\n");
				printf("enable \t index \t type \t title \t adult \t start year \t end year \t runtime \t genres");
				InOrder(sort_startYear);
				break;
			
			case 6:
				printf("\n\nStartYear Decreasing\n");
				printf("enable \t index \t type \t title \t adult \t start year \t end year \t runtime \t genres");
				NotOrder(sort_startYear);
				break;
			
			case 7:
				printf("\n\nEndYear Increasing\n");
				printf("enable \t index \t type \t title \t adult \t start year \t end year \t runtime \t genres");
				InOrder(sort_endYear);
				break;
			
			case 8:
				printf("\n\nEndYear Decreasing\n");
				printf("enable \t index \t type \t title \t adult \t start year \t end year \t runtime \t genres");
				NotOrder(sort_endYear);
				break;

			case 9:
				printf("\n\nRuntime Increasing\n");
				printf("enable \t index \t type \t title \t adult \t start year \t end year \t runtime \t genres");
				InOrder(sort_runtime);
				break;
			
			case 10:
				printf("\n\nRuntime Decreasing\n");
				printf("enable \t index \t type \t title \t adult \t start year \t end year \t runtime \t genres");
				NotOrder(sort_runtime);
				break;
			
			case 11:
				printf("\n\nHelp\n");
				break;

			case 12:
				printf("\n\nQuit\n");
				break;

			default:
				break;
		}
		printf("\n\n");
	}

	printf("\n");

    return 0;
}