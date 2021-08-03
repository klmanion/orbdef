/** entity.c
 */

#include "entity.h"

#include <assert.h>
#include <err.h>


/* memory allocation {{{1 */
/* _alloc() {{{2
 * 	Allocate memory for a Entity struct.
 * 	Shall be freed by entity_free().
 */
entity_t*
entity_alloc(
    entity_t **ptr)
{
	entity_t *entity;

	entity = (entity_t *)malloc(sizeof(struct Entity));
	if (!entity)
	    errx(1,"malloc failure, %s:%d", __FILE__, __LINE__);

	return ptr? (*ptr=entity) : entity;
}

/* _init() {{{2
 * 	Initiallize the memory of the Entity struct.
 * 	Will allocate memory if passed NULL.
 * 	Returns a pointer to the Entity struct.
 *
 * 	Determines the entity's placement absolutely,
 * 	i.e. not relatively.
 * 	Its xo,yo coordinate pair designate its position.
 */
entity_t*
entity_init(
    entity_t	*entity,
    const int	 y,
    const int	 x)
{
	if (!entity)
	    entity = entity_alloc(NULL);

	entity->yo = (int *)malloc(sizeof(int));
	if (!entity->yo)
	    errx(1,"malloc failure, %s:%d", __FILE__, __LINE__);

	entity->xo = (int *)malloc(sizeof(int));
	if (!entity->xo)
	    errx(1,"malloc failure, %s:%d", __FILE__, __LINE__);

	*entity->yo = y;
	*entity->xo = x;

	entity->yd = 0;
	entity->xd = 0;

	entity->rel = false;

	entity->icon = '\0';

	entity->dir = dir_ctr;

	entity->hide = false;

	return entity;
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
entity_t*
entity_init_rel(
    entity_t	*entity,
    int *const	 yo,
    int	*const	 xo,
    const int	 yd,
    const int	 xd)
{
	if (!entity)
	    entity = entity_alloc(NULL);

	entity->yo = yo;
	entity->xo = xo;

	entity->yd = yd;
	entity->xd = xd;

	entity->rel = true;

	entity->icon = '\0';

	entity->dir = dir_ctr;

	entity->hide = false;

	return entity;
}

/* _deinit() {{{2
 * 	Deinitialize the memory of the Entity struct.
 * 	Automatically called by _free().
 * 	Must be called on an statically allocated instance.
 */
entity_t*
entity_deinit(
    entity_t	*entity)
{
	assert (entity);

	if (entity_is_relative(entity))
	    {
		free(entity->yo);	entity->yo = (int *)NULL;
		free(entity->xo);	entity->xo = (int *)NULL;
	    }

	return entity;
}

/* _free() {{{2
 * 	Free memory of a Entity struct pointer.
 * 	Automatically calls _deinit().
 */
entity_t*
entity_free(
    entity_t	**ptr)
{
	assert (ptr);

	free(entity_deinit(*ptr));

	return *ptr = (entity_t *)NULL;
}

/* predicates {{{1 */
/* _is_relative() {{{2
 * 	Returns true if the entity's position is defined relative to a point
 * 	outside itself.
 */
bool
entity_is_relative(
    const entity_t *const	e)
{
	return e->rel;
}

/* _is_visable() {{{2
 */
bool
entity_is_visable(
    const entity_t *const	e)
{
	return !e->hide;
}

/* _is_hidden() {{{2
 */
bool
entity_is_hidden(
    const entity_t *const	e)
{
	return !entity_is_visable(e);
}

/* accessors/mutators {{{1 */
/* _pos_x() {{{2 */
int
entity_pos_y(
    const entity_t *const	e)
{
	assert (e);
	return *e->xo + e->xd;
}

/* _pos_y_set() {{{2 */
int
entity_pos_y_set(
    entity_t *const	e,
    const int		i)
{
	assert (e);

	if (!entity_is_relative(e))
	    return *e->yo = i;
	else
	    return e->yd = i;
}

/* _pos_y() {{{2 */
int
entity_pos_x(
    const entity_t *const	e)
{
	assert (e);
	return *e->yo + e->yd;
}

/* _pos_x_set() {{{2 */
int
entity_pos_x_set(
    entity_t *const	e,
    const int		i)
{
	assert (e);

	if (!entity_is_relative(e))
	    return *e->xo = i;
	else
	    return e->xd = i;
}

/* movement {{{1 */
/* _move() {{{2
 * 	Moves the entity.
 * 	Movement must be checked by calling function.
 */
entity_t*
entity_move(
    entity_t *const	e,
    const int		y,
    const int		x)
{
	assert (e);

	entity_pos_y_set(e, y);
	entity_pos_x_set(e, x);

	return e;
}

/* _delta() {{{2
 * 	Moves entity by the values of the arguments relative to its position
 */
entity_t*
entity_delta(
    entity_t *const	e,
    const int		dy,
    const int		dx)
{
	assert (e);

	entity_pos_y_set(e, entity_pos_y(e) + dy);
	entity_pos_x_set(e, entity_pos_x(e) + dx);

	return e;
}

/* _dir() {{{2
 * 	Move entity in given direction.
 */
entity_t*
entity_mvdir(
    entity_t *const	e,
    const dir_t		dir,
    const int		n)
{
	assert (e);

	if (dir_is_up(dir))
	    entity_delta(e, -n,0);

	if (dir_is_down(dir))
	    entity_delta(e, n,0);

	if (dir_is_left(dir))
	    entity_delta(e, 0,-n);

	if (dir_is_right(dir))
	    entity_delta(e, 0,n);

	return e;
}

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
