/** stbl.c
 */

#include "stbl.h"

#include <ncurses.h>
#include <assert.h>
#include <err.h>
#include "dice.h"
#include "clrpr.h"


/* memory allocation {{{1 */
/* _alloc() {{{2
 * 	Allocate memory for a Stbl struct.
 * 	Shall be freed by stbl_free().
 */
stbl_t*
stbl_alloc(
    stbl_t **ptr)
{
	stbl_t *stbl;

	stbl = (stbl_t *)malloc(sizeof(struct Stbl));
	if (!stbl)
	    errx(1,"malloc failure, %s:%d", __FILE__, __LINE__);

	return ptr? (*ptr=stbl) : stbl;
}

/* _init() {{{2
 * 	Initiallize the memory of the Stbl struct.
 * 	Will allocate memory if passed NULL.
 * 	The six stats must be specified, unlike _init_roll()
 * 	Returns a pointer to the Stbl struct.
 */
stbl_t*
stbl_init(
    stbl_t		*stbl,
    const stat_t	 STR,
    const stat_t	 DEX,
    const stat_t	 CON,
    const stat_t	 INT,
    const stat_t	 WIS,
    const stat_t	 CHR)
{
	if (!stbl)
	    stbl = stbl_alloc(NULL);

	stbl->STR = STR;
	stbl->DEX = DEX;
	stbl->CON = CON;
	stbl->INT = INT;
	stbl->WIS = WIS;
	stbl->CHR = CHR;

	return stbl;
}

/* _init_roll()
 * 	Initiallize the memor of the Stbl struct.
 * 	Will allocate memory if passed NULL.
 * 	Propogates the stat table, unlike _init().
 * 	Returns a pointer to the Stbl struct.
 */
stbl_t*
stbl_init_roll(
    stbl_t	*stbl)
{
	return stbl_init(stbl,
			 dice_roll_str("3d6"),
			 dice_roll_str("3d6"),
			 dice_roll_str("3d6"),
			 dice_roll_str("3d6"),
			 dice_roll_str("3d6"),
			 dice_roll_str("3d6"));
}

/* _deinit() {{{2
 * 	Deinitialize the memory of the Stbl struct.
 * 	Automatically called by _free().
 * 	Must be called on an statically allocated instance.
 */
stbl_t*
stbl_deinit(
    stbl_t	*stbl)
{
	assert (stbl);

	return stbl;
}

/* _free() {{{2
 * 	Free memory of a Stbl struct pointer.
 * 	Automatically calls _deinit().
 */
stbl_t*
stbl_free(
    stbl_t	**ptr)
{
	assert (ptr);

	free(stbl_deinit(*ptr));

	return *ptr = (stbl_t *)NULL;
}

/* stat_norm_mod() {{{1
 * 	All stats are of value 3-18 (3d6).
 *	This distributes the values over the normal curve.
 *	
 *	With 3 rolls of 1-6
 *	    there are a possible 6^3 (=216) possible permutatations of dice sequences.
 *	
 *	    with 16 unique sums (3-18).
 *	
 *	The possible chances of rolling one of these sums are displayed as so:
 *		roll	perms	chance		summed val
 *		====	=====	======		==========
 *		3	1	.004630		.004630
 *		4	3	.013889		.018519
 *		5	6	.027778		.046296
 *		6	10	.046296		.092593
 *		7	15	.069444		.162037
 *		8	22	.101852		.259259
 *		9	25	.115741		.375000
 *		10	27	.125000		.500000
 *		11	27	.125000		.625000
 *		12	25	.115741		.740741
 *		13	21	.097222		.837963
 *		14	15	.069444		.907407
 *		15	10	.046296		.953704
 *		16	6	.027778		.981481
 *		17	3	.013889		.995370
 *		18	1	.004630		1
 *	
 *	Stat Bonuses:
 *		3	-5
 *		4-5	-4
 *		6	-3
 *		7	-2
 *		8-9	-1
 *		10-11	 0
 *		12-13	+1
 *		14	+2
 *		15	+3
 *		16-17	+4
 *		18	+5
 *	
 *	These bonuses are applied to certain checks,
 *	    such as to-hit.
 */
int
stat_norm_mod(
    const stat_t	stat)
{
	static int bonus[18] = {
		-5, -4, -4, -3, -2, -1, -1,
		0, 0,
		+1, +1, +2, +3, +4, +4, +5
	};

	return bonus[stat-1];
}

/* _calc_hp() {{{1
 */
stat_t
stbl_calc_hp(
    const stbl_t *const	stbl,
    const int		basehp)
{
	return basehp + stat_norm_mod(stbl->CON);
}

/* printing {{{1 */
/* _draw() {{{2
 */
void
stbl_draw(
    const stbl_t *const	stbl,
    const int		y,
    const int		x)
{
	attron(CLR(DEFAULT));

	move(y,x);
	printw("STR: %d\tINT: %d", stbl->STR, stbl->INT);
	move(y+1,x);
	printw("DEX: %d\tWIS: %d", stbl->DEX, stbl->WIS);
	move(y+2,x);
	printw("CON: %d\tCHR: %d", stbl->CON, stbl->CHR);

	attroff(CLR(DEFAULT));

	return;
}

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
