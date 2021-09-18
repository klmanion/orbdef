/** pos.h
 */

#ifndef _POS_H_
#define _POS_H_

#include <stdlib.h>
#include <stdbool.h>
#include "dir.h"

typedef
struct Pos
{
	int	*yo;
	int	*xo;

	int	yd;
	int	xd;

	bool	rel;
} pos_t;

pos_t*	pos_alloc (pos_t **);
pos_t*	pos_init (pos_t *,const int,const int);
pos_t*	pos_init_rel (pos_t *,int *const,int *const,const int,const int);
pos_t*	pos_deinit (pos_t *);
pos_t*	pos_free (pos_t **);

bool	pos_is_relative (const pos_t *const);

int	pos_y (const pos_t *const);
int	pos_y_set (pos_t *const,const int);
int	pos_x (const pos_t *const);
int	pos_x_set (pos_t *const,const int);

pos_t*	pos_set (pos_t *const,const int,const int);
pos_t*	pos_delta (pos_t *const,const int,const int);
pos_t*	pos_mvdir (pos_t *const,const dir_t,const int);



#endif /* !_POS_H_ */

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
