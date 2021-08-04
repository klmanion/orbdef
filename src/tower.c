/** tower.c
 */

#include "tower.h"

#include <string.h>
#include <ncurses.h>
#include <assert.h>
#include <err.h>

/* memory allocation {{{1 */
/* _alloc() {{{2
 * 	Allocate memory for a Tower struct.
 * 	Shall be freed by tower_free().
 */
tower_t*
tower_alloc(
    tower_t **ptr)
{
	tower_t *tower;

	tower = (tower_t *)malloc(sizeof(struct Tower));
	if (!tower)
	    errx(1,"malloc failure, %s:%d", __FILE__, __LINE__);

	return ptr? (*ptr=tower) : tower;
}

/* _init() {{{2
 * 	Initiallize the memory of the Tower struct.
 * 	Will allocate memory if passed NULL.
 * 	Returns a pointer to the Tower struct.
 *
 * 	Shall be given central coordinates of stage.
 */
tower_t*
tower_init(
    tower_t 	*tower,
    const int	 y,
    const int	 x)
{
	if (!tower)
	    tower = tower_alloc(NULL);

	entity_init(entity_alloc(&tower->e), y,x);

	memset(tower->shell_lst, (int)NULL, 4);
	tower->shell_num = 0;

	return tower;
}

/* _deinit() {{{2
 * 	Deinitialize the memory of the Tower struct.
 * 	Automatically called by _free().
 * 	Must be called on an statically allocated instance.
 */
tower_t*
tower_deinit(
    tower_t	*tower)
{
	assert (tower);

	entity_free(&tower->e);

	/* TODO */

	return tower;
}

/* _free() {{{2
 * 	Free memory of a Tower struct pointer.
 * 	Automatically calls _deinit().
 */
tower_t*
tower_free(
    tower_t	**ptr)
{
	assert (ptr);

	free(tower_deinit(*ptr));

	return *ptr = (tower_t *)NULL;
}

/* shells {{{1 */
/* _shell_add() {{{2
 * 	Add shell to list of shells.
 * 	TODO: organize shells by radius.
 * 	FIXME: will be deprecated
 * 		shells will be created and maintained
 * 		by spawning at radius 0 and growing
 */
shell_t*
tower_shell_add(
    tower_t *const	t,
    shell_t *const	s)
{
	assert (t);
	assert (s);

	entity_move(s->e, entity_pos_y(t->e),entity_pos_x(t->e));

	return t->shell_lst[t->shell_num++] = s;
}

/* printing {{{1 */
/* _print() {{{2
 */
void
tower_draw(
    const tower_t *const	t)
{
	assert(t);

	for (size_t i=0; i<t->shell_num; ++i)
	    shell_draw(t->shell_lst[i]);

	return;
}

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
