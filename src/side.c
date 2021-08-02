/** side.c
 */

#include "side.h"

#include <ncurses.h>
#include <assert.h>
#include <err.h>
#include "clrpr.h"


/* memory allocation {{{1 */
/* _alloc() {{{2
 * 	Allocate memory for a Side struct.
 * 	Shall be freed by side_free().
 */
side_t*
side_alloc(
    side_t **ptr)
{
	side_t *side;

	side = (side_t *)malloc(sizeof(struct Side));
	if (!side)
	    errx(1,"malloc failure, %s:%d", __FILE__, __LINE__);

	return ptr? (*ptr=side) : side;
}

/* _init() {{{2
 * 	Initiallize the memory of the Side struct.
 * 	Will allocate memory if passed NULL.
 * 	Returns a pointer to the Side struct.
 */
side_t*
side_init(
    side_t *side)
{
	if (!side)
	    side_alloc(&side);

	/* TODO */

	return side;
}

/* _deinit() {{{2
 * 	Deinitialize the memory of the Side struct.
 * 	Automatically called by _free().
 * 	Must be called on an statically allocated instance.
 */
side_t*
side_deinit(
    side_t	*side)
{
	assert (side);

	/* TODO */

	return side;
}

/* _free() {{{2
 * 	Free memory of a Side struct pointer.
 * 	Automatically calls _deinit().
 */
side_t*
side_free(
    side_t	**ptr)
{
	assert (ptr);

	free(side_deinit(*ptr));

	return *ptr = (side_t *)NULL;
}

/* _draw() {{{1
 */
void
side_draw(
    const side_t *const	s)
{
	int y,x;

	getyx(stdscr, y,x);

	for (size_t w=0; w<s->wall_num; ++w)
	    {
		int clr = wall_lst[w]->health;
		attron(CLR(clr));
		mvprintw(y+w,x+w, "%c", s->typ);
		attroff(CLR(clr));
	    }

	return;
}

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
