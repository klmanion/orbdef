/** main.c: orbital defense (orbdef)
 * created by: Kurt L. Manion
 * on: 19 July 2021
 */

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include <time.h>
#include <ncurses.h>
#include "orbdef.h"

#include "soldier.h"

int
main(
    int		argc,
    char *const	argv[])
{
	setlocale(LC_ALL, "");
	setprogname(argv[0]);

	srand(time(NULL));

	/* ncurses initialize */
	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	nonl();
	noecho();
	curs_set(0);

	start_color();
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_GREEN, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);

	refresh();

	orbdef();

	/* ncurses deinitialize */
	endwin();

	return EXIT_SUCCESS;
}

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
