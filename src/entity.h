/** entity.h
 */

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <stdlib.h>
#include <stdbool.h>
#include "dir.h"

typedef
struct Entity
{
	int	*yo;
	int	*xo;

	int	yd;
	int	xd;

	bool	rel;	/* flag for relative position */

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

bool	entity_is_relative (const entity_t *const);
bool	entity_is_visable (const entity_t *const);
bool	entity_is_hidden (const entity_t *const);

int	entity_pos_y (const entity_t *const);
int	entity_pos_y_set (entity_t *const,const int);
int	entity_pos_x (const entity_t *const);
int	entity_pos_x_set (entity_t *const,const int);

entity_t*	entity_move (entity_t *const,const int,const int);
entity_t*	entity_delta (entity_t *const,const int,const int);
entity_t*	entity_mvdir (entity_t *const,const dir_t,const int);

#endif /* !_ENTITY_H_ */

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
