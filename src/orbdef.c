/** orbdef.c
 */

#include "orbdef.h"

#include <stdio.h>
#include <ncurses.h>
#include <stdbool.h>
#include "tower.h"

int
orbdef()
{
	int row,col;
	tower_t tower;
	int ch;

	getmaxyx(stdscr, row,col);
	tower_init(&tower, row/2,col/2);

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

	tower.shell_num = 4;
	tower.shell_lst[0] = shell0;
	tower.shell_lst[1] = shell1;
	tower.shell_lst[2] = shell2;
	tower.shell_lst[3] = shell3;

for (bool running=true; running; )
	    {
		tower_draw(&tower);

		refresh();

		switch ((ch = getch())) {
		case KEY_F(1):
			running = false;

		default:
			break;;
		}
	    }

	tower_deinit(&tower);

	return 1;
}

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
