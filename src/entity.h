/** entity.h
 */

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <stdlib.h>
#include <stdbool.h>
#include "pos.h"
#include "dir.h"

typedef
struct Entity
{
	pos_t	pos;

	char	icon;

	dir_t	dir;	/* direction */

	bool	hide;
} entity_t;

entity_t*	entity_alloc (entity_t **);
entity_t*	entity_init (entity_t *,const int,const int);
entity_t*	entity_init_rel (entity_t *,int *const,int *const,
				 const int,const int);
entity_t*	entity_deinit (entity_t *);
entity_t*	entity_free (entity_t **);

bool	entity_is_visable (const entity_t *const);
bool	entity_is_hidden (const entity_t *const);

#endif /* !_ENTITY_H_ */

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
