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
 */
entity_t*
entity_init(
    entity_t *entity)
{
	if (!entity)
	    entity = entity_alloc(NULL);

	entity->y = entity->x = -1;
	entity->icon = '\0';

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

/* _move() {{{1
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

	e->y = y;
	e->x = x;

	return e;
}

/* _visable() {{{1
 */
bool
entity_visable(
    const entity_t *const	e)
{
	return e->y > -1 && e->x > -1;
}

/* _hidden() {{{1
 */
bool
entity_hidden(
    const entity_t *const	e)
{
	return !entity_visable(e);
}

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
