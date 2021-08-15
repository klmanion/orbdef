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
#include "screen.h"

typedef
struct Common
{
	tower_t	*p0_tl[9];	/* player tower list */
	int	 p0_tn;		/* number of player towers */

	tower_t	*p1_tl[9];	/* enemy tower list */
	int	 p1_tn;		/* number of enemy towers */
} common_data_t;

static	screen_t	*battle =	(screen_t *)NULL;
static	screen_t	*twr_select =	(screen_t *)NULL;

/* battle_run() {{{1 */
screen_t*
battle_run(
    screen_t	*scr,
    void	*vptr)
{
	screen_data_t data;
	common_data_t *cmn;

	chtype ch;
	screen_t *retv;

	data = (screen_data_t)scr->data;
	cmn = (common_data_t *)vptr;

	retv = scr;

	for (bool running=true; running; )
	    {
		/* drawing */
		clear();

		for (size_t n=0; n<cmn->p0_tn; ++n)
		    tower_draw(cmn->p0_tl[n]);
		for (size_t n=0; n<cmn->p1_tn; ++n)
		    tower_draw(cmn->p1_tl[n]);

		refresh();

		/* polling/handling */
		switch ((ch = getch())) {
		case KEY_F(1):
			running = false;
			retv = (screen_t *)NULL;
			break;;

		default:
			break;;
		}
	    }

	return retv;
}

/* twr_select_run() {{{1 */
screen_t*
twr_select_run(
    screen_t	*scr,
    void	*vptr)
{
	screen_data_t data;
	common_data_t *cmn;

	int rows,cols;
	static entity_t cursor;
	int selecting_for;

	chtype ch;

	data = (screen_data_t)scr->data;
	cmn = (common_data_t *)vptr;

	getmaxyx(stdscr, rows,cols);
	entity_init(&cursor, rows/2,cols/2);

	selecting_for = 0;

	for (bool running=true; running; )
	    {
		clear();

		for (size_t n=0; n<cmn->p0_tn; ++n)
		    tower_draw(cmn->p0_tl[n]);
		for (size_t n=0; n<cmn->p1_tn; ++n)
		    tower_draw(cmn->p1_tl[n]);

		move(entity_pos_y(&cursor),entity_pos_x(&cursor));
		addch(inch() & A_CHARTEXT | A_REVERSE);

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
			if (selecting_for == 0)
			    {
				cmn->p0_tl[cmn->p0_tn++] =
					tower_init(NULL,
						   entity_pos_y(&cursor),
						   entity_pos_x(&cursor));

				selecting_for = 1;
			    }
			else if (selecting_for == 1)
			    {
				cmn->p1_tl[cmn->p1_tn++] =
					tower_init(NULL,
						   entity_pos_y(&cursor),
						   entity_pos_x(&cursor));

				running = false;
			    }
			break;;

		default:
			break;;
		}
	    }

	entity_deinit(&cursor);

	return battle;
}

/* orbdef() {{{1 */
int
orbdef()
{
	screen_t *scr, *nscr;
	common_data_t cmn;
	int rows,cols;
	getmaxyx(stdscr, rows,cols);

	screen_init(screen_alloc(&battle),
		    (screen_data_t)NULL,
		    battle_run);
	screen_init(screen_alloc(&twr_select),
		    (screen_data_t)NULL,
		    twr_select_run);

	cmn.p0_tn = 0;
	cmn.p1_tn = 0;

	scr = twr_select;

	while ((nscr = screen_run(scr, (void *)&cmn))) { scr = nscr; }

	for (size_t n=0; n<cmn.p0_tn; ++n)
	    tower_free(&cmn.p0_tl[n]);
	for (size_t n=0; n<cmn.p1_tn; ++n)
	    tower_free(&cmn.p1_tl[n]);

	twr_select = screen_free(&twr_select);
	battle = screen_free(&battle);

	return 1;
}

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
