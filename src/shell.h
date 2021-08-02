/** shell.h
 */

#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdlib.h>
#include "side.h"

typedef
struct Shell
{
	int	radius;
	side_t	side_lst[8];	/* starting from top-left */
} shell_t;

shell_t*	shell_alloc (shell_t **);
shell_t*	shell_init (shell_t *);
shell_t*	shell_deinit (shell_t *);
shell_t*	shell_free (shell_t **);

void	shell_draw (const shell_t *const,const int,const int);

#endif /* !_SHELL_H_ */

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
