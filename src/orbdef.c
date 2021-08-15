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
	tower_t	*spire;

	tower_t	*tower_lst[8];
	int	 tower_num;
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

	tower_t *spire;

	chtype ch;
	screen_t *retv;

	data = (screen_data_t)scr->data;
	cmn = (common_data_t *)vptr;

	spire = cmn->spire;

	retv = scr;

	for (bool running=true; running; )
	    {
		/* drawing */
		clear();

		tower_draw(spire);

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

	chtype ch;
	screen_t *retv;

	data = (screen_data_t)scr->data;
	cmn = (common_data_t *)vptr;

	getmaxyx(stdscr, rows,cols);
	entity_init(&cursor, rows/2,cols/2);

	retv = scr;

	for (bool running=true; running; )
	    {
		clear();

		tower_draw(cmn->spire);

		for (size_t n=0; n<cmn->tower_num; ++n)
		    tower_draw(cmn->tower_lst[n]);

		move(entity_pos_y(&cursor),entity_pos_x(&cursor));
		addch(inch() & A_CHARTEXT | A_REVERSE);

		refresh();

		switch ((ch = getch())) {
		case KEY_F(1):
			running = false;
			retv = battle;
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
			cmn->tower_lst[cmn->tower_num++] = 
				tower_init(NULL,
					   entity_pos_y(&cursor),
					   entity_pos_x(&cursor));
			break;;

		default:
			break;;
		}
	    }

	return retv;
}

/* orbdef() {{{1 */
int
orbdef()
{
	screen_t *scr, *nscr;
	common_data_t cmn;
	int rows,cols;
	tower_t spire;
	getmaxyx(stdscr, rows,cols);

	screen_init(screen_alloc(&battle),
		    (screen_data_t)NULL,
		    battle_run);
	screen_init(screen_alloc(&twr_select),
		    (screen_data_t)NULL,
		    twr_select_run);

//	memset(tower_lst, (int)NULL, 8);
//	tower_num = 0;

	tower_init(&spire, rows/2,cols/2);

//	tower_shell_add(&spire, shell_init(NULL, 0, 0,0));
	tower_shell_add(&spire, shell_init(NULL, 1, 0,0));
	tower_shell_add(&spire, shell_init(NULL, 2, 0,0));
	tower_shell_add(&spire, shell_init(NULL, 3, 0,0));

	cmn.spire = &spire;
	cmn.tower_num = 0;

	/* place surrounding towers */
	scr = twr_select;

	while ((nscr = screen_run(scr, (void *)&cmn))) { scr = nscr; }

	tower_deinit(&spire);

	twr_select = screen_free(&twr_select);
	battle = screen_free(&battle);

	return 1;
}

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
