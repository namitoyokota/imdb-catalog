#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <string.h>
#include "rbt.h"

void curseMenu();
int mainMenu(int, int);
int sortMenu(NODE*, int, int);
int filterMenu(NODE*, int, int);
int searchMenu(NODE*, int, int);
int createMenu(int, int);
int retrieveMenu(int, int);
int updateMenu(int, int);
int deleteMenu(int, int);
int helpMenu(int, int);
NODE* loadMenu(int, int);
void parseFILE(char*, NODE**);

int main(void) {

    int opt = 0;

    if (opt == 0) {
        // terminal
        NODE* RBT = NULL;
        parseFILE("./data/movie_records", &RBT);
        inorder(RBT);

        NODE* result = BST_search(RBT, 630);
        RB_delete(result, RBT);
        //inorder(RBT);
    }

    else {
        initscr();
        noecho();
        cbreak();

        int yMax, xMax;
        getmaxyx(stdscr, yMax, xMax);

        NODE* RBT = loadMenu(yMax, xMax);

        while(1) {
            int choice = mainMenu(yMax, xMax);

            switch(choice) {
                case 0:
                    sortMenu(RBT, yMax, xMax);
                    break;
                case 1:
                    filterMenu(RBT, yMax, xMax);
                    break;
                case 2:
                    searchMenu(RBT, yMax, xMax);
                    break;
                case 3:
                    helpMenu(yMax, xMax);
                    break;
                case 4:
                    return 0;
                default:
                    break;
            }
        }
    }


    return 0;
}

int mainMenu(int yMax, int xMax) {

    char* choices[5] = {"Sort", "Filter", "Search", "Help", "Quit"};
    int choice;
    int highlight = 1;

    WINDOW* main = newwin(yMax, xMax, 0, 0);
    box(main, 0,0);
    wrefresh(main);
    keypad(main, true);
    
    mvwprintw(main, 0, 0, "IMDb Catalog");
    mvwprintw(main, 2, 3, "Use 'up arrow' and 'down arrow' and 'enter' to navigate through the menu");

    // main menu
    while(1) {
        // print highlight
        for (int i=1; i<=5; i++) {
            if (i == highlight)
                wattron(main, A_REVERSE);
            mvwprintw(main, i+3, 2, choices[i-1]);
            wattroff(main, A_REVERSE);
        }
        choice = wgetch(main);

        // switch up and down
        switch(choice) {
            case KEY_UP:
                highlight--;
                if (highlight == 0)
                    highlight = 1;
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight == 6)
                    highlight = 5;
                break;
            default:
                break;
        }

        // on the press of 'enter'
        if (choice == 10)
            break;
    }

    endwin();

    return highlight-1;
}

int sortMenu(NODE* RBT, int yMax, int xMax) {

    char* choices[8] = {"Ascending Index", "Descending Index", "Alphabetical Title", "Ascending Year", "Descending Year",
                        "Ascending Runtime", "Descending Runtime", "Back"};
    int choice;
    int highlight = 1;

    WINDOW* sort = newwin(yMax, xMax, 0, 0);
    box(sort, 0,0);
    wrefresh(sort);
    keypad(sort, true);

    mvwprintw(sort, 0, 0, "Sort Menu");

    while(1) {
        // print highlight
        for (int i=1; i<=8; i++) {
            if (i == highlight)
                wattron(sort, A_REVERSE);
            mvwprintw(sort, i+1, 2, choices[i-1]);
            wattroff(sort, A_REVERSE);
        }
        choice = wgetch(sort);

        // switch up and down
        switch(choice) {
            case KEY_UP:
                highlight--;
                if (highlight == 0)
                    highlight = 1;
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight == 9)
                    highlight = 8;
                break;
            default:
                break;
        }

        // on the press of 'enter'
        if (choice == 10)
            break;
    }

    switch(highlight-1) {
        case 0:
            inorder(RBT);
            wgetch(sort);
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            return 0;
            break;
        default:
            break;
    }

    return 0;
}

int filterMenu(NODE* RBT, int yMax, int xMax) {
    int t = yMax + xMax;

    NODE* result = BST_search(RBT, 335);
    update_index(result, 100);

    return t;
}

int searchMenu(NODE* RBT, int yMax, int xMax) {
    int t = yMax + xMax;

    WINDOW* search = newwin(yMax, xMax, 0, 0);
    box(search, 0,0);
    wrefresh(search);
    keypad(search, true);

    mvwprintw(search, 0, 0, "Search Menu");
    mvwprintw(search, 2, 1, "Search : ");
    char s = mvwgetch(search, 2, 10);
    mvwprintw(search, 2, 10, "%c", s);

    NODE* result = BST_search(RBT, 335);
    update_index(result, 100);

    wgetch(search);

    return t;
}

int createMenu(int yMax, int xMax) {
    int t = yMax + xMax;
    return t;
}

int retrieveMenu(int yMax, int xMax) {
    int t = yMax + xMax;
    return t;
}

int updateMenu(int yMax, int xMax) {
    int t = yMax + xMax;
    return t;
}

int deleteMenu(int yMax, int xMax) {
    int t = yMax + xMax;
    return t;
}

NODE* loadMenu(int yMax, int xMax) {

    WINDOW* load = newwin(yMax, xMax, 0, 0);
    box(load, 0,0);
    wrefresh(load);
    keypad(load, true);

    mvwprintw(load, 0, 0, "Loading...");

    mvwprintw(load, 2, 1, "Press any key to start loading data");
    wgetch(load);

    NODE* RBT = NULL;
    parseFILE("./data/movie_records", &RBT);

    mvwprintw(load, 5, 1, "Loading process has completed. The data is now stored in memory");
    mvwprintw(load, 6, 1, "Press any key to continue..");

    wgetch(load);
    endwin();

    return RBT;
}

int helpMenu(int yMax, int xMax) {

    WINDOW* help = newwin(yMax, xMax, 0, 0);
    box(help, 0,0);
    wrefresh(help);
    keypad(help, true);

    mvwprintw(help, 0, 0, "Help Menu");
    mvwprintw(help, 2, 2, "Keybinds");
    mvwprintw(help, 3, 2, "\t'up arrow'");
    mvwprintw(help, 4, 2, "\t'down arrow'");
    mvwprintw(help, 5, 2, "\t'enter'");
    mvwprintw(help, 6, 2, "Sort");
    mvwprintw(help, 7, 2, "\tIndex : ascending and descending");
    mvwprintw(help, 8, 2, "\tTitle : aphabetical");
    mvwprintw(help, 9, 2, "\tYear : ascending and descending");
    mvwprintw(help, 10, 2, "\tRuntime : ascending and descending");
    mvwprintw(help, 12, 2, "Press any key to continue..");

    wgetch(help);
    endwin();

    return 0;
}

void parseFILE(char *tsvfile, NODE** RBT) {
	FILE *fp;
	fp = fopen(tsvfile, "r");

	if (fp == 0) {
		printf("Error\n");
		return;
	} else {
		char line[300];
		int row=0, col=0;
		while (fgets(line, 300, fp) && row < 30) {
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

			row++;col=0;
		}
	}
}