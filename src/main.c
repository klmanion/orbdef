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
#include "clrpr.h"
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
	init_pair(CLRPR_WHITE,		COLOR_WHITE,	COLOR_BLACK);
	init_pair(CLRPR_RED,		COLOR_RED,	COLOR_BLACK);
	init_pair(CLRPR_BROWN,		COLOR_YELLOW,	COLOR_BLACK);
	init_pair(CLRPR_BLUE,		COLOR_BLUE,	COLOR_BLACK);
	init_pair(CLRPR_GREEN,		COLOR_GREEN,	COLOR_BLACK);
	init_pair(CLRPR_MAGENTA,	COLOR_MAGENTA,	COLOR_BLACK);

	init_pair(CLRPR_SELECT_TARGET,	COLOR_BLACK,	COLOR_GREEN);
	init_pair(CLRPR_SELECT_PLAYER,	COLOR_BLACK,	COLOR_WHITE);
	init_pair(CLRPR_SELECT_ENEMY,	COLOR_BLACK,	COLOR_RED);
	init_pair(CLRPR_SELECT_SQUAD,	COLOR_BLACK,	COLOR_YELLOW);
	init_pair(CLRPR_SELECT_ITEM,	COLOR_BLACK,	COLOR_BLUE);

	refresh();

	orbdef();

	/* ncurses deinitialize */
	endwin();

	return EXIT_SUCCESS;
}

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
