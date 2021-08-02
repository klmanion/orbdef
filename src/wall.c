/** wall.c
 */

#include "wall.h"

#include <ncurses.h>
#include <assert.h>
#include <err.h>
#include "clrpr.h"


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
    wall_t *wall)
{
	if (!wall)
	    wall = wall_alloc(NULL);

	wall->def = 1;

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

	/* TODO */

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

/* _color() {{{1
 * 	Return the COLOR_PAIR to attribute the wall token.
 * 	Controlled by current defense.
 * 		0:	red
 * 		1:	white
 * 		2:	brown
 * 		3:	blue
 * 		4:	green
 * 		5:	magenta
 */

int
wall_color(
    const wall_t *const	w)
{
	assert (w);

	switch (w->def) {
	case 0:
		return CLRPR_RED;
	case 1:
		return CLRPR_WHITE;
	case 2:
		return CLRPR_BROWN;
	case 3:
		return CLRPR_BLUE;
	case 4:
		return CLRPR_GREEN;
	case 5:
		return CLRPR_MAGENTA;
	}

	return CLRPR_DEFAULT;	/* will never reach */
}

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
