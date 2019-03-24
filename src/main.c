#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <time.h>
#include "../lib/stack.h"
#include "../lib/rbt.h"
#include "../lib/crud.h"
#include "../lib/logger.h"

// MENU
int mainMenu(int, int);
RBT* loadMenu(int, int);
    // sort, filter, search
    int sortMenu(int, int);
    int filterMenu(int, int);
    int searchMenu(int, int);
    // CRUD
    int editMenu(int, int, char*);
    int createMenu(int, int);
    int retrieveMenu(int, int, char*);
    int updateMenu(int, int, char*);
    int deleteMenu(int, int, char*);
    // other
    int helpMenu(int, int);
    void clearBox(WINDOW*, int, int);
// FILE IO
void parseFILE(char*, RBT**);
void updateRBT();
void checkLog(char*);

STACK* LIST;
RBT* RBT_INDEX;
RBT* RBT_TITLE;
RBT* RBT_YEAR;
RBT* RBT_RUNTIME;

char str[30];
char filename[30];

int main(void) {

    initscr();
    noecho();
    cbreak();
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    RBT_INDEX = loadMenu(yMax, xMax);
    RBT_EXPORT_RUNTIME(RBT_INDEX, &RBT_RUNTIME);
    RBT_EXPORT_YEAR(RBT_INDEX, &RBT_YEAR);
    RBT_EXPORT_TITLE(RBT_INDEX, &RBT_TITLE);

    WINDOW* initial  = newwin(yMax, xMax, 0, 0);
    box(initial, 0,0);
    wrefresh(initial);
    keypad(initial, true);

    mvwprintw(initial, 0, 0, "Getting Started");

    echo();
    mvwprintw(initial, 2, 1, "Enter username (this will determine your .log filename)");
    mvwprintw(initial, 3, 2, ">> ");
    wgetstr(initial, str);

    checkLog(str);
    clearBox(initial, yMax, xMax);

    endwin();

    while(1) {
        int choice = mainMenu(yMax, xMax);
        switch(choice) {
            case 0:
                sortMenu(yMax, xMax);
                break;
            case 1:
                filterMenu(yMax, xMax);
                break;
            case 2:
                searchMenu(yMax, xMax);
                break;
            case 3:
                editMenu(yMax, xMax, "");
                break;
            case 4:
                helpMenu(yMax, xMax);
                break;
            case 5:
                return 0;
            default:
                break;
        }
    }
    return 0;
}

int mainMenu(int yMax, int xMax) {

    char* choices[6] = {"Sort", "Filter", "Search", "CRUD", "Help", "Quit"};
    int choice;
    int highlight = 1;

    WINDOW* main = newwin(yMax, xMax, 0, 0);
    box(main, 0,0);
    wrefresh(main);
    keypad(main, true);

    noecho();
    mvwprintw(main, 0, 0, "IMDb Catalog");
    mvwprintw(main, 2, 3, "Use 'up arrow' and 'down arrow' and 'enter' to navigate through the menu");

    // main menu
    while(1) {
        // print highlight
        for (int i=1; i<=6; i++) {
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
                    highlight = 6;
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight == 7)
                    highlight = 1;
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

int sortMenu(int yMax, int xMax) {

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
                    highlight = 8;
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight == 9)
                    highlight = 1;
                break;
            default:
                break;
        }

        // on the press of 'enter'
        if (choice == 10)
            break;
    }

    clearBox(sort, yMax, xMax);
    setMax(yMax-5);

    switch(highlight-1) {
        case 0:
            INORDER_STACK(RBT_INDEX, LIST);
            break;
        case 1:
            OUTORDER_STACK(RBT_INDEX, LIST);
            break;
        case 2:
            INORDER_STACK(RBT_TITLE, LIST);
            break;
        case 3:
            INORDER_STACK(RBT_YEAR, LIST);
            break;
        case 4:
            OUTORDER_STACK(RBT_YEAR, LIST);
            break;
        case 5:
            INORDER_STACK(RBT_RUNTIME, LIST);
            break;
        case 6:
            OUTORDER_STACK(RBT_RUNTIME, LIST);
            break;
        case 7:
            return 0;
        default:
            break;
    }

    mvwprintw(sort, 2, 2, "INDEX\tTITLE\tYEAR\tRUNTIME\tGENRES\tMEDIA\tDATE");
    for (int i=4; i<yMax-5; i++) {
        if (empty()) break;
        pop(sort, i);
    }
    freeStack();

    echo();
    mvwprintw(sort, yMax-3, 2, "Enter index to edit or 'q' to quit");
    mvwprintw(sort, yMax-2, 3, ">> ");
    wgetstr(sort, str);

    if (strcmp(str, "q") != 0 && strcmp(str, "") !=0) editMenu(yMax, xMax, str);

    return 0;
}

int filterMenu(int yMax, int xMax) {
    char* choices[5] = {"Set Minimum Year", "Set Maximum Year", "Set Minimum Runtime", "Set Maximum Runtime", "Back"};
    int choice;
    int highlight = 1;

    WINDOW* filter = newwin(yMax, xMax, 0, 0);
    box(filter, 0,0);
    wrefresh(filter);
    keypad(filter, true);

    mvwprintw(filter, 0, 0, "Filter Menu");

    while(1) {
        // print highlight
        for (int i=1; i<=5; i++) {
            if (i == highlight)
                wattron(filter, A_REVERSE);
            mvwprintw(filter, i+1, 2, choices[i-1]);
            wattroff(filter, A_REVERSE);
        }
        choice = wgetch(filter);

        // switch up and down
        switch(choice) {
            case KEY_UP:
                highlight--;
                if (highlight == 0)
                    highlight = 5;
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight == 6)
                    highlight = 1;
                break;
            default:
                break;
        }

        // on the press of 'enter'
        if (choice == 10)
            break;
    }

    echo();
    clearBox(filter, yMax, xMax);
    setMax(yMax-5);

    switch(highlight-1) {
        case 0:
            mvwprintw(filter, 2, 1, "Year");   
            mvwprintw(filter, 3, 2, ">> ");
            wgetstr(filter, str);
            INORDER_TREE_WALK_YEAR_BIGGER(RBT_YEAR, atoi(str));
            break;
        case 1:
            mvwprintw(filter, 2, 1, "Year");   
            mvwprintw(filter, 3, 2, ">> ");
            wgetstr(filter, str);
            INORDER_TREE_WALK_YEAR_SMALLER(RBT_YEAR, atoi(str));
            break;
        case 2:
            mvwprintw(filter, 2, 1, "Runtime");   
            mvwprintw(filter, 3, 2, ">> ");
            wgetstr(filter, str);
            INORDER_TREE_WALK_RUNTIME_BIGGER(RBT_RUNTIME, atoi(str));
            break;
        case 3:
            mvwprintw(filter, 2, 1, "Runtime");   
            mvwprintw(filter, 3, 2, ">> ");
            wgetstr(filter, str);
            INORDER_TREE_WALK_RUNTIME_SMALLER(RBT_RUNTIME, atoi(str));
            break;
        case 4:
            OUTORDER_STACK(RBT_YEAR, LIST);
            break;
        case 5:
            INORDER_STACK(RBT_RUNTIME, LIST);
            break;
        case 6:
            OUTORDER_STACK(RBT_RUNTIME, LIST);
            break;
        case 7:
            return 0;
        default:
            break;
    }

    clearBox(filter, yMax, xMax);
    mvwprintw(filter, 2, 2, "INDEX\tTITLE\tYEAR\tRUNTIME\tGENRES\tMEDIA\tDATE");
    for (int i=4; i<yMax-5; i++) {
        if (empty()) break;
        pop(filter, i);
    }
    freeStack();

    echo();
    mvwprintw(filter, yMax-3, 2, "Enter index to edit or 'q' to quit");
    mvwprintw(filter, yMax-2, 3, ">> ");
    wgetstr(filter, str);

    if (strcmp(str, "q") != 0 && strcmp(str, "") !=0) editMenu(yMax, xMax, str);

    return 0;
}

int searchMenu(int yMax, int xMax) {

    char* choices[4] = {"By Index", "By Title", "By Genre", "Back"};
    int choice;
    int highlight = 1;

    WINDOW* search = newwin(yMax, xMax, 0, 0);
    box(search, 0,0);
    wrefresh(search);
    keypad(search, true);

    echo();

    mvwprintw(search, 0, 0, "Search Menu");

    while(1) {
        // print highlight
        for (int i=1; i<=4; i++) {
            if (i == highlight)
                wattron(search, A_REVERSE);
            mvwprintw(search, i+1, 2, choices[i-1]);
            wattroff(search, A_REVERSE);
        }
        choice = wgetch(search);

        // switch up and down
        switch(choice) {
            case KEY_UP:
                highlight--;
                if (highlight == 0)
                    highlight = 4;
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight == 5)
                    highlight = 1;
                break;
            default:
                break;
        }

        // on the press of 'enter'
        if (choice == 10)
            break;
    }

    char str[30];
    clearBox(search, yMax, xMax);

    switch(highlight-1) {
        case 0:
            mvwprintw(search, 2, 1, "Index : ");   
            wgetstr(search, str);
            TREE_SEARCH_LIST_INDEX(RBT_INDEX, atoi(str));
            break;
        case 1:
            mvwprintw(search, 2, 1, "Title : "); 
            wgetstr(search, str);
            TREE_SEARCH_LIST_TITLE(RBT_TITLE, str);
            break;
        case 2:
            mvwprintw(search, 2, 1, "Genre : "); 
            wgetstr(search, str);
            TREE_SEARCH_LIST_GENRE(RBT_TITLE, str);
            break;
        default:
            return 0;
    }

    clearBox(search, yMax, xMax);

    mvwprintw(search, 2, 2, "INDEX\tTITLE\tYEAR\tRUNTIME\tGENRES\tMEDIA\tDATE");
    for (int i=4; i<yMax-5; i++) {
        if (empty()) break;
        pop(search, i);
    }
    freeStack();

    echo();
    mvwprintw(search, yMax-3, 2, "Enter index to edit or 'q' to quit");
    mvwprintw(search, yMax-2, 3, ">> ");
    wgetstr(search, str);

    if (strcmp(str, "q") != 0 && strcmp(str, "") !=0) editMenu(yMax, xMax, str);

    return 0;
}

int editMenu(int yMax, int xMax, char* input) {

    char* choices[5] = {"CREATE MOVIE", "RETRIEVE MOVIE", "UPDATE MOVIE", "DELETE MOVIE", "BACK"};
    int choice;
    int highlight = 1;

    WINDOW* edit = newwin(yMax, xMax, 0, 0);
    box(edit, 0,0);
    wrefresh(edit);
    keypad(edit, true);

    mvwprintw(edit, 0, 0, "Edit Menu");

    while(1) {
        // print highlight
        for (int i=1; i<=5; i++) {
            if (i == highlight)
                wattron(edit, A_REVERSE);
            mvwprintw(edit, i+1, 2, choices[i-1]);
            wattroff(edit, A_REVERSE);
        }
        choice = wgetch(edit);

        // switch up and down
        switch(choice) {
            case KEY_UP:
                highlight--;
                if (highlight == 0)
                    highlight = 5;
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight == 6)
                    highlight = 1;
                break;
            default:
                break;
        }

        // on the press of 'enter'
        if (choice == 10)
            break;
    }

    clearBox(edit, yMax, xMax);
    setMax(yMax-5);

    switch(highlight-1) {
        case 0:
            createMenu(yMax, xMax);
            break;
        case 1:
            retrieveMenu(yMax, xMax, input);
            break;
        case 2:
            updateMenu(yMax, xMax, input);
            break;
        case 3:
            deleteMenu(yMax, xMax, input);
            break;
        case 4:
            return 0;
        default:
            break;
    }

    return 0;
}

int createMenu(int yMax, int xMax) {
    WINDOW* create = newwin(yMax, xMax, 0, 0);
    box(create, 0,0);
    wrefresh(create);
    keypad(create, true);

    echo();
    char index[10], title[30], year[10], runtime[10], genres[30], media[20], y[5], m[3], d[3];

    mvwprintw(create, 0, 0, "Create Menu");
    mvwprintw(create, 2, 1, "Index");
    mvwprintw(create, 3, 2, ">> ");
    wgetstr(create, index);
    mvwprintw(create, 4, 1, "Title");
    mvwprintw(create, 5, 2, ">> ");
    wgetstr(create, title);
    mvwprintw(create, 6, 1, "Year");
    mvwprintw(create, 7, 2, ">> ");
    wgetstr(create, year);
    mvwprintw(create, 8, 1, "Runtime");
    mvwprintw(create, 9, 2, ">> ");
    wgetstr(create, runtime);
    mvwprintw(create, 10, 1, "Genres");
    mvwprintw(create, 11, 2, ">> ");
    wgetstr(create, genres);
    mvwprintw(create, 12, 1, "Media");
    mvwprintw(create, 13, 2, ">> ");
    wgetstr(create, media);
    mvwprintw(create, 14, 1, "Year");
    mvwprintw(create, 15, 2, ">> ");
    wgetstr(create, y);
    mvwprintw(create, 16, 1, "Month");
    mvwprintw(create, 17, 2, ">> ");
    wgetstr(create, m);
    mvwprintw(create, 18, 1, "Day");
    mvwprintw(create, 19, 2, ">> ");
    wgetstr(create, d);

    CREATE_MOVIE(filename, &RBT_INDEX, index, title, year, runtime, genres, media, m, d, y);
    updateRBT();

    endwin();

    return 0;
}

int retrieveMenu(int yMax, int xMax, char* input) {

    WINDOW* retrieve = newwin(yMax, xMax, 0, 0);
    box(retrieve, 0,0);
    wrefresh(retrieve);
    keypad(retrieve, true);

    mvwprintw(retrieve, 0, 0, "Retrieve Menu");

    clearBox(retrieve, yMax, xMax);
    INORDER_TREE_WALK_DELETED(RBT_INDEX);
    mvwprintw(retrieve, 2, 2, "INDEX\tTITLE\tYEAR\tRUNTIME\tGENRES\tMEDIA\tDATE");
    for (int i=4; i<yMax-5; i++) {
        if (empty()) break;
        pop(retrieve, i);
    }
    freeStack();

    if (strcmp(input, "") == 0) {
        // ask
        echo();
        mvwprintw(retrieve, yMax-3, 1, "Enter the index of the movie to retrieve");
        mvwprintw(retrieve, yMax-2, 2, ">> ");
        wgetstr(retrieve, str);
        RETRIEVE_MOVIE(filename, &RBT_INDEX, str);
    } else {
        RETRIEVE_MOVIE(filename, &RBT_INDEX, input);
    }
    updateRBT();

    endwin();

    return 0;
}

int updateMenu(int yMax, int xMax, char* input) {
    WINDOW* update = newwin(yMax, xMax, 0, 0);
    box(update, 0,0);
    wrefresh(update);
    keypad(update, true);

    echo();
    char index[10], title[30], year[10], runtime[10], genres[30], media[20], y[5], m[3], d[3];

    mvwprintw(update, 0, 0, "Update Menu");
    mvwprintw(update, 2, 1, "Index");
    mvwprintw(update, 3, 2, ">> ");
    wgetstr(update, index);
    mvwprintw(update, 4, 1, "Title");
    mvwprintw(update, 5, 2, ">> ");
    wgetstr(update, title);
    mvwprintw(update, 6, 1, "Year");
    mvwprintw(update, 7, 2, ">> ");
    wgetstr(update, year);
    mvwprintw(update, 8, 1, "Runtime");
    mvwprintw(update, 9, 2, ">> ");
    wgetstr(update, runtime);
    mvwprintw(update, 10, 1, "Genres");
    mvwprintw(update, 11, 2, ">> ");
    wgetstr(update, genres);
    mvwprintw(update, 12, 1, "Media");
    mvwprintw(update, 13, 2, ">> ");
    wgetstr(update, media);
    mvwprintw(update, 14, 1, "Year");
    mvwprintw(update, 15, 2, ">> ");
    wgetstr(update, y);
    mvwprintw(update, 16, 1, "Month");
    mvwprintw(update, 17, 2, ">> ");
    wgetstr(update, m);
    mvwprintw(update, 18, 1, "Day");
    mvwprintw(update, 19, 2, ">> ");
    wgetstr(update, d);

    UPDATE_MOVIE(filename, &RBT_INDEX, index, title, year, runtime, genres, media, m, d, y);
    updateRBT();

    endwin();

    return 0;
}

int deleteMenu(int yMax, int xMax, char* input) {

    WINDOW* delete = newwin(yMax, xMax, 0, 0);
    box(delete, 0,0);
    wrefresh(delete);
    keypad(delete, true);

    mvwprintw(delete, 0, 0, "Delete Menu");

    if (strcmp(input, "") == 0) {
        // ask
        echo();
        mvwprintw(delete, 2, 1, "Enter the index of the movie to delete");
        mvwprintw(delete, 3, 2, ">> ");
        wgetstr(delete, str);
        DELETE_MOVIE(filename, &RBT_INDEX, str);
    } else {
        DELETE_MOVIE(filename, &RBT_INDEX, input);
    }
    updateRBT();

    endwin();

    return 0;
}

RBT* loadMenu(int yMax, int xMax) {
    WINDOW* load = newwin(yMax, xMax, 0, 0);
    box(load, 0,0);
    wrefresh(load);
    keypad(load, true);

    mvwprintw(load, 0, 0, "Loading...");

    mvwprintw(load, 2, 1, "Press any key to start loading data");
    wgetch(load);

    parseFILE("./data/movie_records.tsv", &RBT_INDEX);

    mvwprintw(load, 5, 1, "Loading process has completed. The data is now stored in memory");
    mvwprintw(load, 6, 1, "Press any key to continue..");

    wgetch(load);
    endwin();

    return RBT_INDEX;
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

void clearBox(WINDOW* win, int yMax, int xMax) {
    for (int j=1; j<yMax-1; j++) {
        for (int i=1; i<xMax-1; i++) {
            mvwprintw(win, j, i, " ");
        }
    }
    return;
}

void parseFILE(char *tsvfile, RBT** RBT) {
	FILE *fp = fopen(tsvfile, "r");
	if (fp == 0) printf("Error\n");
	else {
        time_t t = time(NULL); struct tm tm = *localtime(&t);
		char line[300]; int row=0, col=0;
		while (fgets(line, 300, fp) && row < 100000) {
			strtok(line, "\n"); char *ptr = strdup(line), *word, *index, *title, *year, *runtime, *genres;
			while ((word = strsep(&ptr, "\t"))) {
                if (strcmp(word, "\\N") == 0) word = "(null)";
				switch(col) {
					case 0: word[0]='0'; word[1]='0'; index = word; break;
					case 2: title = word; break;
					case 5: year = word; break;
					case 7: runtime = word; break;
					case 8: genres = word; break;
					default: break;
				}
				if (strcmp(word, "\0") == 0) break;
				col++;
			}
			*RBT = RB_INSERT_INDEX(*RBT, '1', atoi(index), title, atoi(year), atoi(runtime), genres, NULL, tm.tm_mon+1, tm.tm_mday, tm.tm_year+1900);
			row++; col=0;
		}
	}
    fclose(fp);
}

void updateRBT() {
    RBT_EXPORT_RUNTIME(RBT_INDEX, &RBT_RUNTIME);
    RBT_EXPORT_YEAR(RBT_INDEX, &RBT_YEAR);
    RBT_EXPORT_TITLE(RBT_INDEX, &RBT_TITLE);
}

void checkLog(char* username) {
    strcpy(filename, "./log/"); strcat(filename, username); strcat(filename, ".log");
    readLog(filename, &RBT_INDEX);
}