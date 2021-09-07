/** tower.h
 */

#ifndef _TOWER_H_
#define _TOWER_H_

#include <stdlib.h>
#include <stdbool.h>
#include "shell.h"
#include "stbl.h"

typedef
struct Tower
{
	shell_t	*shell_lst[4];
	int	 shell_num;

	int	id;
	bool	is_enemy;

	stbl_t	stbl;

	entity_t	*e;
} tower_t;

tower_t*	tower_alloc (tower_t **);
tower_t*	tower_init (tower_t *,const int,const int,const bool);
tower_t*	tower_deinit (tower_t *);
tower_t*	tower_free (tower_t **);

shell_t*	tower_shell_add (tower_t *const,shell_t *const);

void	tower_draw (const tower_t *const);
char	id_char (const int);

#endif /* !_TOWER_H_ */

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
