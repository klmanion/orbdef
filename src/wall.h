/** wall.h
 */

#ifndef _WALL_H_
#define _WALL_H_

#include <stdlib.h>
#include "entity.h"

typedef
struct Wall
{
	char	tok;	/* token */

	entity_t	*e;
} wall_t;

wall_t*	wall_alloc (wall_t **);
wall_t*	wall_init (wall_t *,const char,int *const,int *const,
		   const int,const int);
wall_t*	wall_deinit (wall_t *);
wall_t*	wall_free (wall_t **);

void	wall_draw (const wall_t *const,const int,const int);

#endif /* !_WALL_H_ */

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
