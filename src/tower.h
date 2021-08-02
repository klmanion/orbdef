/** tower.h
 */

#ifndef _TOWER_H_
#define _TOWER_H_

#include <stdlib.h>
#include "shell.h"

typedef
struct Tower
{
	int	y;
	int	x;

	int	 shell_num;
	shell_t	*shell_lst[4];
} tower_t;

tower_t*	tower_alloc (tower_t **);
tower_t*	tower_init (tower_t *,const int,const int);
tower_t*	tower_deinit (tower_t *);
tower_t*	tower_free (tower_t **);

void	tower_draw (const tower_t *const);

#endif /* !_TOWER_H_ */

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
