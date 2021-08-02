/** soldier.c
 */

#include "soldier.h"

#include <ncurses.h>
#include <assert.h>
#include <err.h>
#include "clrpr.h"


/* memory allocation {{{1 */
/* _alloc() {{{2
 * 	Allocate memory for a Soldier struct.
 * 	Shall be freed by soldier_free().
 */
soldier_t*
soldier_alloc(
    soldier_t **ptr)
{
	soldier_t *soldier;

	soldier = (soldier_t *)malloc(sizeof(struct Soldier));
	if (!soldier)
	    errx(1,"malloc failure, %s:%d", __FILE__, __LINE__);

	return ptr? (*ptr=soldier) : soldier;
}

/* _init() {{{2
 * 	Initiallize the memory of the Soldier struct.
 * 	Will allocate memory if passed NULL.
 * 	Returns a pointer to the Soldier struct.
 */
soldier_t*
soldier_init(
    soldier_t		*soldier,
    const soldier_typ	 styp,
    stbl_t		*stbl,
    const bool		 is_enemy)
{
	if (styp == undefined)
	    return (soldier_t *)NULL;

	if (!soldier)
	    soldier = soldier_alloc(NULL);

	entity_init(entity_alloc(&soldier->e));

	soldier->styp = styp;

	if (!stbl)
	    stbl = stbl_init_roll(NULL);
	soldier->stbl = stbl;

	soldier->hp = soldier->maxhp =
		stbl_calc_hp(soldier->stbl,
			     dice_roll_str(basehp[soldier->styp]));

	soldier->is_enemy = is_enemy;

	soldier->e->icon = icon[soldier->styp];

	return soldier;
}

/* _deinit() {{{2
 * 	Deinitialize the memory of the Soldier struct.
 * 	Automatically called by _free().
 * 	Must be called on an statically allocated instance.
 */
soldier_t*
soldier_deinit(
    soldier_t	*soldier)
{
	assert (soldier);

	entity_free(&soldier->e);

	return soldier;
}

/* _free() {{{2
 * 	Free memory of a Soldier struct pointer.
 * 	Automatically calls _deinit().
 */
soldier_t*
soldier_free(
    soldier_t	**ptr)
{
	assert (ptr);

	free(soldier_deinit(*ptr));

	return *ptr = (soldier_t *)NULL;
}

/* _draw()
 */
void
soldier_draw(
    const soldier_t *const	sld)
{
	int clrpr;

	clrpr = sld->is_enemy? CLRPR_ENEMY : CLRPR_WHITE;

	attron(COLOR_PAIR(clrpr));

	mvprintw(sld->e->y,sld->e->x, "%c", sld->e->icon);

	attroff(COLOR_PAIR(clrpr));

	return;
}

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
