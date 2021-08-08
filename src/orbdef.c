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
} common_data_t;

screen_t*
battle_run(
    screen_t *const	 scr,
    void		*vptr)
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

int
orbdef()
{
	screen_t *battle;
	screen_t *scr;
	common_data_t cmn;
	int row,col;
	tower_t spire;
//	tower_t	*tower_lst[8];
//	int	 tower_num;

	screen_init(screen_alloc(&battle),
		    (screen_data_t)NULL,
		    battle_run);

//	memset(tower_lst, (int)NULL, 8);
//	tower_num = 0;

	getmaxyx(stdscr, row,col);
	tower_init(&spire, row/2,col/2);

	tower_shell_add(&spire, shell_init(NULL, 0, 0,0));
	tower_shell_add(&spire, shell_init(NULL, 1, 0,0));
	tower_shell_add(&spire, shell_init(NULL, 2, 0,0));
	tower_shell_add(&spire, shell_init(NULL, 3, 0,0));

	cmn.spire = &spire;

	/* place surrounding towers */
//	entity_t cursor;
//
//	entity_init(&cursor, row/2,col/2);
//
//	for (bool running=true; running; )
//	    {
//		clear();
//
//		tower_draw(&spire);
//
//		for (size_t n=0; n<tower_num; ++n)
//		    tower_draw(tower_lst[n]);
//
//		attron(A_REVERSE);
//		move(entity_pos_y(&cursor),entity_pos_x(&cursor));
//		addch(inch() & A_CHARTEXT);
//		attroff(A_REVERSE);
//
//		refresh();
//
//		switch ((ch = getch())) {
//		case KEY_F(1):
//			running = false;
//			break;;
//
//		/* TODO: may not create tower in spire's radius */
//		/* TODO: bound checking */
//		/* TODO: cursor object */
//		case 'j':
//		case KEY_DOWN:
//			entity_mvdir(&cursor, dir_bot, 1);	break;;
//		case 'k':
//		case KEY_UP:
//			entity_mvdir(&cursor, dir_top, 1);	break;;
//		case 'h':
//		case KEY_LEFT:
//			entity_mvdir(&cursor, dir_cl, 1);	break;;
//		case 'l':
//		case KEY_RIGHT:
//			entity_mvdir(&cursor, dir_cr, 1);	break;;
//		case 'y':
//			entity_mvdir(&cursor, dir_tl, 1);	break;;
//		case 'u':
//			entity_mvdir(&cursor, dir_tr, 1);	break;;
//		case 'b':
//			entity_mvdir(&cursor, dir_bl, 1);	break;;
//		case 'n':
//			entity_mvdir(&cursor, dir_br, 1);	break;;
//
//		case '\r':	/* place tower */
//			tower_lst[tower_num++] = 
//				tower_init(NULL,
//					   entity_pos_y(&cursor),
//					   entity_pos_x(&cursor));
//			break;;
//
//		default:
//			break;;
//		}
//	    }

	scr = battle;
	while ((scr = screen_run(scr, (void *)&cmn))) { }

	tower_deinit(&spire);

	battle = screen_free(&battle);

	return 1;
}

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
