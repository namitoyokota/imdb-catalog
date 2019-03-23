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
    int createMenu(int, int);
    int retrieveMenu(int, int);
    int updateMenu(int, int);
    int deleteMenu(int, int);
    // other
    int helpMenu(int, int);
    void clearBox(WINDOW*, int, int);
// FILE IO
void parseFILE(char*, RBT**);

RBT* RBT_INDEX;
RBT* RBT_TITLE;
RBT* RBT_YEAR;
RBT* RBT_RUNTIME;








int main(void) {

    // 0 = read, 1 = write
    int enable = 0;
    int opt = 1;

    // console ui
    if (opt == 0) {

        char* username = "namito";
        char filename[30] = "./logs/"; strcat(filename, username); strcat(filename, ".log");

        parseFILE("./data/movie_records.tsv", &RBT_INDEX);

        if (enable == 0) {
            readLog(filename, &RBT_INDEX);
            //INORDER_TREE_WALK(RBT);

            printf("\n\nsearch don\n");

            //RBT* search = NULL;
            //TREE_SEARCH_LIST_TITLE(RBT, &search, "don");
            //INORDER_TREE_WALK(search);

            //TREE_SEARCH_LIST_INDEX(RBT, &search, 1000);
            //INORDER_TREE_WALK(search);
        } else {    
            printf("\nadded 1000\n");
            CREATE_MOVIE(filename, &RBT_INDEX, "1000", "Title of the New Movie", "2019", "90", "Comedy", "DVD", "10", "30", "2018");
            //INORDER_TREE_WALK(RBT);

            printf("\ndeleting 335\n");
            DELETE_MOVIE(filename, &RBT_INDEX, "335");
            printf("\nupdating 502\n");
            UPDATE_MOVIE(filename, &RBT_INDEX, "502", "Namito", "1999", "90", "Comedy,Fantasy", "BluRay", "8", "13", "1999");
            //INORDER_TREE_WALK(RBT);
        }

        /*
        printf("\n\ndeleted list\n");
        INORDER_TREE_WALK_DELETED(RBT);

        printf("\n\nyear greater than 1900\n");  
        INORDER_TREE_WALK_YEAR_BIGGER(RBT, 1900);

        printf("\n\nruntime greater than 0\n");  
        INORDER_TREE_WALK_YEAR_BIGGER(RBT, 0);

        printf("\n\nyear smaller than 1900\n");  
        INORDER_TREE_WALK_YEAR_SMALLER(RBT, 1900);

        printf("\n\ndrama genre\n");  
        INORDER_TREE_WALK_GENRES(RBT, "Drama");
        */
    }

    // curses ui
    else {
        initscr();
        noecho();
        cbreak();

        int yMax, xMax;
        getmaxyx(stdscr, yMax, xMax);
        RBT_INDEX = loadMenu(yMax, xMax);
        RBT_EXPORT_RUNTIME(RBT_INDEX, &RBT_RUNTIME);
        RBT_EXPORT_YEAR(RBT_INDEX, &RBT_YEAR);
        RBT_EXPORT_TITLE(RBT_INDEX, &RBT_TITLE);

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

    clearBox(sort, yMax, xMax);

    STACK* s;
    setMax(yMax-5);

    switch(highlight-1) {
        case 0:
            INORDER_STACK(RBT_INDEX, s);
            break;
        case 1:
            OUTORDER_STACK(RBT_INDEX, s);
            break;
        case 2:
            INORDER_STACK(RBT_TITLE, s);
            break;
        case 3:
            INORDER_STACK(RBT_YEAR, s);
            break;
        case 4:
            OUTORDER_STACK(RBT_YEAR, s);
            break;
        case 5:
            INORDER_STACK(RBT_RUNTIME, s);
            break;
        case 6:
            OUTORDER_STACK(RBT_RUNTIME, s);
            break;
        case 7:
            return 0;
            break;
        default:
            break;
    }

    mvwprintw(sort, 2, 2, "INDEX\tTITLE\tYEAR\tRUNTIME\tGENRES\tMEDIA\tDATE");
    for (int i=4; i<yMax-5; i++) {
        if (empty()) break;
        pop(sort, i);
    }
    wgetch(sort);

    return 0;
}

int filterMenu(int yMax, int xMax) {
    int t = yMax + xMax;

    return t;
}

int searchMenu(int yMax, int xMax) {

    char* choices[5] = {"By Index", "By Title", "By Year", "By Runtime", "Back"};
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
        for (int i=1; i<=5; i++) {
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

    char str[30];

    switch(highlight-1) {
        case 0:
            clearBox(search, yMax, xMax);
            mvwprintw(search, 2, 1, "Index : ");   
            wgetstr(search, str);
            //RBT* search_result = NULL;
            //TREE_SEARCH_LIST_INDEX(RBT, &search_result, atoi(str));
            //mvwprintw(search, 4, 1, "TItle: %s", search_result->title);
            break;
        case 1:
            clearBox(search, yMax, xMax);
            mvwprintw(search, 2, 1, "Title : "); 
            break;
        case 2:
            clearBox(search, yMax, xMax);
            mvwprintw(search, 2, 1, "Year : "); 
            break;
        case 3:
            clearBox(search, yMax, xMax);
            mvwprintw(search, 2, 1, "Runtime : "); 
            break;
        case 4:
            return 0;
            break;
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

    char index[10], title[30], year[10], runtime[10], genres[30];

    mvwprintw(create, 0, 0, "Create Menu");
    mvwprintw(create, 2, 1, "Index : ");
    wgetstr(create, index);
    mvwprintw(create, 3, 1, "Title : ");
    wgetstr(create, title);
    mvwprintw(create, 4, 1, "Year : ");
    wgetstr(create, year);
    mvwprintw(create, 5, 1, "Runtime : ");
    wgetstr(create, runtime);
    mvwprintw(create, 6, 1, "Generes : ");
    wgetstr(create, genres);

    return 0;
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
		while (fgets(line, 300, fp) && row < 1000) {
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