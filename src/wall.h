/** wall.h
 */

#ifndef _WALL_H_
#define _WALL_H_

#include <stdlib.h>

typedef
struct Wall
{
	int	def;
} wall_t;

wall_t*	wall_alloc (wall_t **);
wall_t*	wall_init (wall_t *);
wall_t*	wall_deinit (wall_t *);
wall_t*	wall_free (wall_t **);

int	wall_color (const wall_t *const);

#endif /* !_WALL_H_ */

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
