/** orbdef.c
 */

#include "orbdef.h"

#include <stdio.h>
#include <ncurses.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "clrpr.h"
#include "pair.h"
#include "dir.h"
#include "entity.h"	/* may remove after cursor is implemented */
#include "tower.h"
#include "screen.h"

typedef
struct Common
{
	head_t	plr_lst;
	head_t	enm_lst;
} common_data_t;

static	screen_t	*battle =	(screen_t *)NULL;
static	screen_t	*stage_set =	(screen_t *)NULL;
static	screen_t	*selection =	(screen_t *)NULL;

/* static helpers {{{1 */
/* tower_lst_draw() {{{2 */
void
tower_lst_draw(
    head_t *lst)
{
	pair_t *var;

	STAILQ_FOREACH(var, lst, cdr)
	    {
		tower_draw((tower_t *)var->car);
	    }

	return;
}

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

		tower_lst_draw(&cmn->plr_lst);
		tower_lst_draw(&cmn->enm_lst);
		    		
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

	pair_t *p;

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

		tower_lst_draw(&cmn->plr_lst);
		tower_lst_draw(&cmn->enm_lst);

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
			p = pair_init_car(NULL,
					  (void *)tower_init(NULL,
							     entity_pos_y(&cursor),
							     entity_pos_x(&cursor),
							     (bool)selecting_for));

			STAILQ_INSERT_TAIL(selecting_for == sf_player ? &cmn->plr_lst : &cmn->enm_lst, p, cdr);
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

/* selection_run() {{{1 */
screen_t*
selection_run(
    screen_t	*scr,
    void	*vptr)
{
	common_data_t *cmn;
	screen_data_t data;

	pair_t *var;
	head_t *lst;

	int rows,cols;
	chtype ch;

	enum {
		friend=7,
		enemy,
		squad,
		item
	} selecting;

	tower_t *target;

	bool blink;
	int bctr,btmr;	/* blink timer */

	cmn = (common_data_t *)scr->cmn;
	data = (screen_data_t)scr->data;

	getmaxyx(stdscr, rows,cols);

	selecting = friend;

	target = (tower_t *)NULL;

	blink = false;
	bctr = 0;
	btmr = 5;

	for (bool running=true; running; )
	    {
		clear();

		tower_lst_draw(&cmn->plr_lst);
		tower_lst_draw(&cmn->enm_lst);
		
		if (!blink)
		    {
			switch (selecting) {
			case friend:
			case enemy:
				if (selecting == friend)
				    lst = &cmn->plr_lst;
				else
				    lst = &cmn->enm_lst;

				STAILQ_FOREACH(var, lst, cdr)
				    {
					tower_t *t;

					if (selecting == friend)
					    attron(CLR(SELECT_FRIEND));
					else if (selecting == enemy)
					    attron(CLR(SELECT_ENEMY));

					t = (tower_t *)var->car;
					mvprintw(entity_pos_y(t->e),
						 entity_pos_x(t->e),
						 "%c", id_char(t->id));

					if (selecting == friend)
					    attroff(CLR(SELECT_FRIEND));
					else if (selecting == enemy)
					    attroff(CLR(SELECT_ENEMY));
				    }

				if (target)
				    {
					attron(CLR(SELECT_TARGET));

					mvprintw(entity_pos_y(target->e),
						 entity_pos_x(target->e),
						 "%c", id_char(target->id));

					attroff(CLR(SELECT_TARGET));
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

		if (target)
		    {
			stbl_draw(&target->stbl, rows-5,0);
		    }
		
		refresh();

		switch ((ch = getch())) {
		case KEY_F(1):
			running = false;
			break;;

		case '-':
			if (selecting == friend)
			    selecting = enemy;
			else if (selecting == enemy)
			    selecting = friend;
			break;;

		case '`':
			if (target)
			    target = (tower_t *)NULL;
			else
			    return NULL;;
			break;;

		default:
			if (isalpha(ch))
			    {
				int n;

				n = ch - 'a';

				lst = selecting == friend ? &cmn->plr_lst : &cmn->enm_lst;

				STAILQ_FOREACH(var, lst, cdr)
				    {
					if (((tower_t *)var->car)->id == n)
					    target = (tower_t *)var->car;
				    }

			    }

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
	pair_t *var, *tvar;
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

	STAILQ_INIT(&cmn.plr_lst);
	STAILQ_INIT(&cmn.enm_lst);

	scr = stage_set;

	while ((scr = screen_run(scr, NULL))) { }

	STAILQ_FOREACH_SAFE(var, &cmn.plr_lst, cdr, tvar)
	    {
		tower_free((tower_t **)&var->car);
	    }
	STAILQ_FOREACH_SAFE(var, &cmn.enm_lst, cdr, tvar)
	    {
		tower_free((tower_t **)&var->car);
	    }
	    
	selection = screen_free(&selection);
	stage_set = screen_free(&stage_set);
	battle = screen_free(&battle);

	return 1;
}

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
