/** orbdef.c
 */

#include "orbdef.h"

#include <stdio.h>
#include <ncurses.h>
#include <stdbool.h>
#include <string.h>
#include "dir.h"
#include "entity.h"	/* may remove after cursor is implemented */
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

	tower_shell_add(&spire, shell_init(NULL, 0, 0,0));
	tower_shell_add(&spire, shell_init(NULL, 1, 0,0));
	tower_shell_add(&spire, shell_init(NULL, 2, 0,0));
	tower_shell_add(&spire, shell_init(NULL, 3, 0,0));
	tower_draw(&spire);

	refresh();	getch();
	return 0;

	/* place surrounding towers */
	entity_t cursor;

	entity_init(&cursor, row/2,col/2);

	for (bool running=true; running; )
	    {
		clear();

		tower_draw(&spire);

		for (size_t n=0; n<tower_num; ++n)
		    tower_draw(tower_lst[n]);

		attron(A_REVERSE);
		move(entity_pos_y(&cursor),entity_pos_x(&cursor));
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
			entity_mvdir(&cursor, dir_bot, 1);	break;;
		case 'k':
		case KEY_UP:
			entity_mvdir(&cursor, dir_top, 1);	break;;
		case 'h':
		case KEY_LEFT:
			entity_mvdir(&cursor, dir_cl, 1);	break;;
		case 'l':
		case KEY_RIGHT:
			entity_mvdir(&cursor, dir_cr, 1);	break;;
		case 'y':
			entity_mvdir(&cursor, dir_tl, 1);	break;;
		case 'u':
			entity_mvdir(&cursor, dir_tr, 1);	break;;
		case 'b':
			entity_mvdir(&cursor, dir_bl, 1);	break;;
		case 'n':
			entity_mvdir(&cursor, dir_br, 1);	break;;

		case '\r':	/* place tower */
			tower_lst[tower_num++] = 
				tower_init(NULL,
					   entity_pos_y(&cursor),
					   entity_pos_x(&cursor));
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
