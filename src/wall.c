/** wall.c
 */

#include "wall.h"

#include <ncurses.h>
#include <assert.h>
#include <err.h>


/* memory allocation {{{1 */
/* _alloc() {{{2
 * 	Allocate memory for a Wall struct.
 * 	Shall be freed by wall_free().
 */
wall_t*
wall_alloc(
    wall_t **ptr)
{
	wall_t *wall;

	wall = (wall_t *)malloc(sizeof(struct Wall));
	if (!wall)
	    errx(1,"malloc failure, %s:%d", __FILE__, __LINE__);

	return ptr? (*ptr=wall) : wall;
}

/* _init() {{{2
 * 	Initiallize the memory of the Wall struct.
 * 	Will allocate memory if passed NULL.
 * 	Returns a pointer to the Wall struct.
 */
wall_t*
wall_init(
    wall_t	*wall,
    const char	 tok,
    int *const	 yo,
    int *const	 xo,
    const int	 yd,
    const int	 xd)
{
	if (!wall)
	    wall = wall_alloc(NULL);

	entity_init_rel(entity_alloc(&wall->e), yo,xo, yd,xd);

	wall->tok = tok;

	return wall;
}

/* _deinit() {{{2
 * 	Deinitialize the memory of the Wall struct.
 * 	Automatically called by _free().
 * 	Must be called on an statically allocated instance.
 */
wall_t*
wall_deinit(
    wall_t	*wall)
{
	assert (wall);

	wall->e = entity_free(&wall->e);

	return wall;
}

/* _free() {{{2
 * 	Free memory of a Wall struct pointer.
 * 	Automatically calls _deinit().
 */
wall_t*
wall_free(
    wall_t	**ptr)
{
	assert (ptr);

	free(wall_deinit(*ptr));

	return *ptr = (wall_t *)NULL;
}

/* drawing {{{1 */
/* _draw() {{{2 */
void
wall_draw(
    const wall_t *const	wall,
    const int		oy,
    const int		ox)
{
	assert (wall);
	mvprintw(pos_y(&wall->e->pos),pos_x(&wall->e->pos),
		 "%c", wall->tok);
	return;
}

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
