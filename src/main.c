#include <stdio.h>
#include <stdlib.h>
#include "parse.h"
#include "rbt.h"

int mainMenu();
int sortMenu();
int filterMenu();

int main(void) {

 	NODE* RBT = NULL;

	parseFILE("./data/movie_records", &RBT);

	// before
	printf("\nInorder\n");
	inorder(RBT);

	/*
	// create
	RBT = RB_insert(RBT, '0', 9999, "Elf", 1990, 90, "Comedy;Family;Fantasy");

	// delete
	NODE* a = BST_search(RBT, 574);
	update_enable(a, 0);
	a = BST_search(RBT, 630);
	update_enable(a, 0);

	// update
    a = BST_search(RBT,502);
	update_index(a, 100);
	update_title(a,"Namito");
	update_year(a, 9999);
	update_runtime(a, 24);
	update_genres(a, "Comedy");

	// retrieve
	a = BST_search(RBT, 630);
	update_enable(a, 1);

	// after
	printf("\nInorder\n");
	inorder(RBT);
	*/

	printf("\n");
    return 0;
}

int mainMenu() {
	int menu;
	printf(" ___________________________________________\n");
	printf("|                                           |\n");
	printf("|                  MENU                     |\n");
	printf("|   1. SORT MENU                            |\n");
	printf("|   2. FILTER MENU                          |\n");
	printf("|   3. HELP                                 |\n");
	printf("|   4. QUIT                                 |\n");
	printf("|___________________________________________|\n");
	printf("\n\tChoice : ");
	scanf("%d", &menu);
	printf("\n\n");
	return menu;
}

int sortMenu() {
	int menu;
	printf(" ___________________________________________\n");
	printf("|                                           |\n");
	printf("|                SORT MENU                  |\n");
	printf("|   1. PRINT INDEX IN INCREASING ORDER      |\n");
	printf("|   2. PRINT INDEX IN DECREASING ORDER      |\n");
	printf("|   3. PRINT TITLE IN INCREASING ORDER      |\n");
	printf("|   4. PRINT TITLE IN DECREASING ORDER      |\n");
	printf("|   5. PRINT YEAR IN INCREASING ORDER       |\n");
	printf("|   6. PRINT YEAR IN DECREASING ORDER       |\n");
	printf("|   7. PRINT RUNTIME IN INCREASING ORDER    |\n");
	printf("|   8. PRINT RUNTIME IN DECREASING ORDER   |\n");
	printf("|   9. BACK                                |\n");
	printf("|   10. HELP                                |\n");
	printf("|   11. QUIT                                |\n");
	printf("|___________________________________________|\n");
	printf("\n\tChoice : ");
	scanf("%d", &menu);
	printf("\n\n");
	return menu;
}

int filterMenu() {
	int menu;
	printf(" ___________________________________________\n");
	printf("|                                           |\n");
	printf("|               FILTER MENU                 |\n");
	printf("|   1. BACK                                 |\n");
	printf("|   2. HELP                                 |\n");
	printf("|   3. QUIT                                 |\n");
	printf("|___________________________________________|\n");
	printf("\n\tChoice : ");
	scanf("%d", &menu);
	printf("\n\n");
	return menu;
}