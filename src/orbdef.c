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
#include "clrpr.h"

typedef
struct Common
{
	tower_t	*p0_tl[9];	/* player tower list */
	int	 p0_tn;		/* number of player towers */

	tower_t	*p1_tl[9];	/* enemy tower list */
	int	 p1_tn;		/* number of enemy towers */
} common_data_t;

static	screen_t	*battle =	(screen_t *)NULL;
static	screen_t	*stage_set=	(screen_t *)NULL;
static	screen_t	*selection =	(screen_t *)NULL;

/* battle_run() {{{1 */
screen_t*
battle_run(
    screen_t	*scr,
    void	*vptr)
{
	common_data_t *cmn;
	screen_data_t data;

	chtype ch;
	screen_t *retv;

	cmn = (common_data_t *)scr->cmn;
	data = (screen_data_t)scr->data;

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

		case 's':
			screen_run(selection, NULL);
			break;;

		default:
			break;;
		}
	    }

	return retv;
}

/* stage_set_run() {{{1 */
screen_t*
stage_set_run(
    screen_t	*scr,
    void	*vptr)
{
	common_data_t *cmn;
	screen_data_t data;

	int rows,cols;
	static entity_t cursor;
	enum {
		sf_player=0,
		sf_enemy=1
	} selecting_for;

	chtype ch;

	cmn = (common_data_t *)scr->cmn;
	data = (screen_data_t)scr->data;

	getmaxyx(stdscr, rows,cols);
	entity_init(&cursor, rows/2,cols/2);

	selecting_for = sf_player;	/* select enemy position first */

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
			if (selecting_for == sf_player)
			    {
				cmn->p0_tl[cmn->p0_tn++] =
					tower_init(NULL,
						   entity_pos_y(&cursor),
						   entity_pos_x(&cursor));
			    }
			else if (selecting_for == sf_enemy)
			    {
				cmn->p1_tl[cmn->p1_tn++] =
					tower_init(NULL,
						   entity_pos_y(&cursor),
						   entity_pos_x(&cursor));

				cmn->p1_tl[cmn->p1_tn-1]->is_enemy = true;
			    }
			break;;

		case ' ':	/* switch between player and enemy */
			selecting_for = !selecting_for;
			break;;

		case '`':	/* finish */
			running = false;
			break;;

		default:
			break;;
		}
	    }

	entity_deinit(&cursor);

	return battle;
}

/* selection() {{{1 */
screen_t*
selection_run(
    screen_t	*scr,
    void	*vptr)
{
	common_data_t *cmn;
	screen_data_t data;

	int rows,cols;
	chtype ch;

	enum {
		friend=6,
		enemy,
		squad,
		item
	} selecting;

	bool blink;
	int bctr,btmr;	/* blink timer */

	cmn = (common_data_t *)scr->cmn;
	data = (screen_data_t)scr->data;

	getmaxyx(stdscr, rows,cols);

	selecting = friend;

	blink = false;
	bctr = 0;
	btmr = 5;

	for (bool running=true; running; )
	    {
		clear();

		mvprintw(0,0, "selecting");

		for (size_t n=0; n<cmn->p0_tn; ++n)
		    tower_draw(cmn->p0_tl[n]);
		for (size_t n=0; n<cmn->p1_tn; ++n)
		    tower_draw(cmn->p1_tl[n]);

		if (!blink)
		    {
			switch (selecting) {
			case friend:
				for (size_t n=0; n<cmn->p0_tn; ++n)
				    {
					tower_t *t;

					t = cmn->p0_tl[n];

					attrset(0);
					attron(CLR(SELECT_FRIEND));

					mvprintw(entity_pos_y(t->e),
						 entity_pos_x(t->e),
						 "%c", t->id);

					attrset(0);	/* TODO: remove after
							   other printing code
							   uses attrset(0) */

				    }

				if (++bctr >= btmr)
				    blink = true;

				break;;
			}
		    }
		else
		    {
			blink = false;
			bctr = 0;
		    }

		refresh();

		switch ((ch = getch())) {
		case KEY_F(1):
			running = false;
			break;;

		case '`':
			return NULL;

		default:
			break;;
		}
	    }

	return scr;
}

/* orbdef() {{{1 */
int
orbdef()
{
	screen_t *scr;
	common_data_t cmn;
	int rows,cols;
	getmaxyx(stdscr, rows,cols);

	screen_init(screen_alloc(&battle),
		    (void *)&cmn,
		    (screen_data_t)NULL,
		    battle_run);
	screen_init(screen_alloc(&stage_set),
		    (void *)&cmn,
		    (screen_data_t)NULL,
		    stage_set_run);
	screen_init(screen_alloc(&selection),
		    (void *)&cmn,
		    (screen_data_t)NULL,
		    selection_run);

	cmn.p0_tn = 0;
	cmn.p1_tn = 0;

	scr = stage_set;

	while ((scr = screen_run(scr, NULL))) { }

	for (size_t n=0; n<cmn.p0_tn; ++n)
	    tower_free(&cmn.p0_tl[n]);
	for (size_t n=0; n<cmn.p1_tn; ++n)
	    tower_free(&cmn.p1_tl[n]);

	selection = screen_free(&selection);
	stage_set = screen_free(&stage_set);
	battle = screen_free(&battle);

	return 1;
}

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
