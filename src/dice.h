/** dice.h
 */

#ifndef _DICE_H_
#define _DICE_H_

#include <stdlib.h>
#include <stdbool.h>

typedef
struct Dice
{
	int	n;
	int	a;
	int	p;

	bool	is_constant;
	int	constant;
} dice_t;

dice_t*	dice_alloc (dice_t **);
dice_t*	dice_init (dice_t *,const char *);
dice_t*	dice_deinit (dice_t *);
dice_t*	dice_free (dice_t **);

int	dice_roll (const dice_t *const);
int	dice_roll_str (const char *);

#endif /* !_DICE_H_ */

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
