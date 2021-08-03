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


} shell_t;

shell_t*	shell_alloc (shell_t **);
shell_t*	shell_init (shell_t *,const int);
shell_t*	shell_deinit (shell_t *);
shell_t*	shell_free (shell_t **);

char**	shell_image (const shell_t *const);

int	shell_rows (const shell_t *const);
int	shell_cols (const shell_t *const);
int	shell_walls_num (const shell_t *const);

void	shell_draw (const shell_t *const,const int,const int);

#endif /* !_SHELL_H_ */

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
