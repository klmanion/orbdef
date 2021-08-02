/** stbl.h
 */

#ifndef _STBL_H_
#define _STBL_H_

#include <stdlib.h>

typedef	int	stat_t;

typedef
struct Stbl
{
	stat_t	ATK;
	stat_t	DEX;
	stat_t	CON;

	stat_t	INT;
	stat_t	WIS;
	stat_t	CHR;
} stbl_t;

stbl_t*	stbl_alloc (stbl_t **);
stbl_t*	stbl_init (stbl_t *,const stat_t,const stat_t,const stat_t,
		   const stat_t,const stat_t,const stat_t);
stbl_t*	stbl_init_roll (stbl_t *);
stbl_t*	stbl_deinit (stbl_t *);
stbl_t*	stbl_free (stbl_t **);

int	stat_norm_mod (const stat_t);
stat_t	stbl_calc_hp (const stbl_t *const,const int);

#endif /* !_STBL_H_ */

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
