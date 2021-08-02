/** side.h
 */

#ifndef _SIDE_H_
#define _SIDE_H_

#include <stdlib.h>
#include "wall.h"

typedef
enum side_type
{
	tl	= '/',
	top	= '-',
	tr	= '\\',
	r	= '|',
	br	= '/',
	bot	= '-',
	bl	= '\\',
	l	= '|'
} side_typ;

typedef
struct Side
{
	side_typ	typ;

	int	wall_num;
	wall_t	wall_lst[7];
} side_t;

side_t*	side_alloc (side_t **);
side_t*	side_init (side_t *);
side_t*	side_deinit (side_t *);
side_t*	side_free (side_t **);

void	side_draw (const side_t *const);

#endif /* !_SIDE_H_ */

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
