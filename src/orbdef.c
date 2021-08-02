/** orbdef.c
 */

#include "orbdef.h"

#include <stdio.h>
#include <ncurses.h>
#include <stdbool.h>
#include <string.h>
#include "tower.h"

static	tower_t	*tower_lst[8];
static	int	 tower_num;

int
orbdef()
{
	int row,col;
	tower_t spire;
	int ch;

	memset(tower_lst, (int)NULL, 8);
	tower_num = 0;

	getmaxyx(stdscr, row,col);
	tower_init(&spire, row/2,col/2);

	shell_t *shell0 = NULL;
	shell0 = shell_init(NULL);
	shell0->radius = 0;

	shell_t *shell1 = NULL;
	shell1 = shell_init(shell1);
	shell1->radius = 1;

	shell_t *shell2 = NULL;
	shell2 = shell_init(shell2);
	shell2->radius = 2;

	shell_t *shell3 = NULL;
	shell3 = shell_init(shell3);
	shell3->radius = 3;

	spire.shell_num = 4;
	spire.shell_lst[0] = shell0;
	spire.shell_lst[1] = shell1;
	spire.shell_lst[2] = shell2;
	spire.shell_lst[3] = shell3;

	/* place surrounding towers */
	int cy,cx;	/* cursor y,x */

	cy = row/2;
	cx = col/2;

	for (bool running=true; running; )
	    {
		clear();

		tower_draw(&spire);

		for (size_t n=0; n<tower_num; ++n)
		    tower_draw(tower_lst[n]);

		attron(A_REVERSE);
		move(cy,cx);
		addch(inch() & A_CHARTEXT);
		attroff(A_REVERSE);

		refresh();

		switch ((ch = getch())) {
		case KEY_F(1):
			running = false;
			break;;

		/* TODO: may not create tower in spire's radius */
		/* TODO: bound checking */
		/* TODO: cursor object */
		case 'j':
		case KEY_DOWN:
			++cy;	break;;
		case 'k':
		case KEY_UP:
			--cy;	break;;
		case 'h':
		case KEY_LEFT:
			--cx;	break;;
		case 'l':
		case KEY_RIGHT:
			++cx;	break;;

		case '\r':	/* place tower */
			tower_lst[tower_num++] = tower_init(NULL, cy,cx);
			break;;

		default:
			break;;
		}
	    }
#ifdef DEBUG
	return 1;
#endif

	for (bool running=true; running; )
	    {
		tower_draw(&spire);

		refresh();

		switch ((ch = getch())) {
		case KEY_F(1):
			running = false;

		default:
			break;;
		}
	    }

	tower_deinit(&spire);

	return 1;
}

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
