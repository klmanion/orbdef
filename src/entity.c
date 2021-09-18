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

	pos_init(&entity->pos, y,x);

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

	pos_init_rel(&entity->pos, yo,xo, yd,xd);

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

	pos_deinit(&entity->pos);

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

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
