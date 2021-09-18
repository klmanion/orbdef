/** pos.c
 */

#include "pos.h"

#include <assert.h>
#include <err.h>


/* memory allocation {{{1 */
/* _alloc() {{{2
 * 	Allocate memory for a Pos struct.
 * 	Shall be freed by pos_free().
 */
pos_t*
pos_alloc(
    pos_t **ptr)
{
	pos_t *pos;

	pos = (pos_t *)malloc(sizeof(struct Pos));
	if (!pos)
	    errx(1,"malloc failure, %s:%d", __FILE__, __LINE__);

	return ptr? (*ptr=pos) : pos;
}

/* _init() {{{2
 * 	Initiallize the memory of the Pos struct.
 * 	Will allocate memory if passed NULL.
 * 	Returns a pointer to the Pos struct.
 *
 * 	Determines the entity's placement absolutely,
 * 	i.e. not relatively.
 * 	Its xo,yo coordinate pair designate its position.
 */
pos_t*
pos_init(
    pos_t	*pos,
    const int	 y,
    const int	 x)
{
	if (!pos)
	    pos = pos_alloc(NULL);

	pos->yo = (int *)malloc(sizeof(int));
	if (!pos->yo)
	    errx(1,"malloc failure, %s:%d", __FILE__, __LINE__);

	pos->xo = (int *)malloc(sizeof(int));
	if (!pos->xo)
	    errx(1,"malloc failure, %s:%d", __FILE__, __LINE__);

	*pos->yo = y;
	*pos->xo = x;

	pos->yd = 0;
	pos->xd = 0;

	pos->rel = false;

	return pos;
}

/* _init_rel() {{{2
 * 	Initiallize the memory of the Entity struct.
 * 	Will allocate memory if passed NULL.
 * 	Returns a pointer to the Entity struct.
 *
 * 	Determines the entity's placement relatively,
 * 	i.e. relative to a position outside of the entity.
 * 	Its xd,yx coordinate pair is an offset to the
 * 	coordinate pointed to by xo,yo.
 */
pos_t*
pos_init_rel(
    pos_t	*pos,
    int *const	 yo,
    int	*const	 xo,
    const int	 yd,
    const int	 xd)
{
	if (!pos)
	    pos = pos_alloc(NULL);

	pos->yo = yo;
	pos->xo = xo;

	pos->yd = yd;
	pos->xd = xd;

	pos->rel = true;

	return pos;
}

/* _deinit() {{{2
 * 	Deinitialize the memory of the Pos struct.
 * 	Automatically called by _free().
 * 	Must be called on an statically allocated instance.
 */
pos_t*
pos_deinit(
    pos_t	*pos)
{
	assert (pos);

	if (pos->yo)
	    free(pos->yo),pos->yo = (int *)NULL;
	if (pos->xo)
	    free(pos->xo),pos->xo = (int *)NULL;

	if (pos_is_relative(pos))
	    {
		free(pos->yo);	pos->yo = (int *)NULL;
		free(pos->xo);	pos->xo = (int *)NULL;
	    }

	return pos;
}

/* _free() {{{2
 * 	Free memory of a Pos struct pointer.
 * 	Automatically calls _deinit().
 */
pos_t*
pos_free(
    pos_t	**ptr)
{
	assert (ptr);

	free(pos_deinit(*ptr));

	return *ptr = (pos_t *)NULL;
}

/* predicates {{{1 */
/* _is_relative() {{{2
 */
bool
pos_is_relative(
    const pos_t *const	p)
{
	return p->rel;
}

/* accessors/mutators {{{1 */
/* _y() {{{2 */
int
pos_y(
    const pos_t *const	p)
{
	assert (p);
	return *p->yo + p->yd;
}

/* _y_set() {{{2 */
int
pos_y_set(
    pos_t *const	p,
    const int		i)
{
	assert (p);

	if (!pos_is_relative(p))
	    return *p->yo = i;
	else
	    return p->yd = i;
}

/* _x() {{{2 */
int
pos_x(
    const pos_t *const	p)
{
	assert (p);
	return *p->xo + p->xd;
}

/* _x_set() {{{2 */
int
pos_x_set(
    pos_t *const	p,
    const int		i)
{
	assert (p);

	if (!pos_is_relative(p))
	    return *p->xo = i;
	else
	    return p->xd = i;
}

/* _set() {{{2
 * 	Moves the pos.
 * 	Movement must be checked by calling function.
 */
pos_t*
pos_set(
    pos_t *const	p,
    const int		y,
    const int		x)
{
	assert (p);

	pos_y_set(p, y);
	pos_x_set(p, x);

	return p;
}

/* _delta() {{{2
 * 	Moves pos by the values of the arguments relative to its position
 */
pos_t*
pos_delta(
    pos_t *const	p,
    const int		dy,
    const int		dx)
{
	assert (p);

	pos_y_set(p, pos_y(p) + dy);
	pos_x_set(p, pos_x(p) + dx);

	return p;
}

/* _dir() {{{2
 * 	Move pos in given direction.
 */
pos_t*
pos_mvdir(
    pos_t *const	p,
    const dir_t		dir,
    const int		n)
{
	assert (p);

	if (dir_is_up(dir))
	    pos_delta(p, -n,0);

	if (dir_is_down(dir))
	    pos_delta(p, n,0);

	if (dir_is_left(dir))
	    pos_delta(p, 0,-n);

	if (dir_is_right(dir))
	    pos_delta(p, 0,n);

	return p;
}

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
