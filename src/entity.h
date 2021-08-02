/** entity.h
 */

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <stdlib.h>
#include <stdbool.h>
#include "stbl.h"

typedef
struct Entity
{
	int	y;
	int	x;

	char	icon;
} entity_t;

entity_t*	entity_alloc (entity_t **);
entity_t*	entity_init (entity_t *);
entity_t*	entity_deinit (entity_t *);
entity_t*	entity_free (entity_t **);

entity_t*	entity_move (entity_t *const,const int,const int);
bool		entity_visable (const entity_t *const);
bool		entity_hidden (const entity_t *const);

#endif /* !_ENTITY_H_ */

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
