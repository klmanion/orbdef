/** dice.c
 */

#include "dice.h"

#include <string.h>
#include <assert.h>
#include <err.h>


/* memory allocation {{{1 */
/* _alloc() {{{2
 * 	Allocate memory for a Dice struct.
 * 	Shall be freed by dice_free().
 */
dice_t*
dice_alloc(
    dice_t **ptr)
{
	dice_t *dice;

	dice = (dice_t *)malloc(sizeof(struct Dice));
	if (!dice)
	    errx(1,"malloc failure, %s:%d", __FILE__, __LINE__);

	return ptr? (*ptr=dice) : dice;
}

/* _init() {{{2
 * 	Initiallize the memory of the Dice struct.
 * 	Will allocate memory if passed NULL.
 * 	Returns a pointer to the Dice struct.
 *
 * 	A roll is a number of dice with a modifier:
 * 		ndp+a
 * 	where n is the number of rolls of a dice with p pips
 * 	with an addend applied once after the rolling of the dice.
 * 	`d' is a syntactic element present in each dice string.
 * 	Absent a `d' string is assumed to be a number taken as a constant
 * 	result of the dice throw.
 *
 * 	Assumes correct syntax.
 */
dice_t*
dice_init(
    dice_t	*dice,
    const char	*str)
{
	char *dptr, *aptr;
	char dest[80];

	if (!dice)
	    dice = dice_alloc(NULL);

	dptr = strchr(str, 'd');

	if (!dptr)
	    {
		dice->is_constant = true;
		dice->constant = atoi(str);
		return dice;
	    }
	else
	    {
		dice->is_constant = false;
		dice->constant = -1;
	    }

	dice->n = dptr==str? 1 : atoi(strncpy(dest, str, dptr - str));

	aptr = strchr(str, '+');
	dice->a = !aptr? 0 : atoi(aptr+1);

	if (aptr)
	    dice->p = atoi(strncpy(dest, dptr+1, aptr-dptr-1));
	else
	    dice->p = atoi(strcpy(dest, dptr+1));

	return dice;
}

/* _deinit() {{{2
 * 	Deinitialize the memory of the Dice struct.
 * 	Automatically called by _free().
 * 	Must be called on an statically allocated instance.
 */
dice_t*
dice_deinit(
    dice_t	*dice)
{
	assert (dice);

	/* TODO */

	return dice;
}

/* _free() {{{2
 * 	Free memory of a Dice struct pointer.
 * 	Automatically calls _deinit().
 */
dice_t*
dice_free(
    dice_t	**ptr)
{
	assert (ptr);

	free(dice_deinit(*ptr));

	return *ptr = (dice_t *)NULL;
}

/* rolling {{{1 */
/* _roll() {{{2
 */
int
dice_roll(
    const dice_t *const	dice)
{
	int acc;

	if (dice->is_constant)
	    {
		return dice->constant;
	    }
	else
	    {
		acc = 0;

		for (int n=dice->n; n>0; --n)
		    acc += rand() % dice->p;

		return acc + dice->a;
	    }
}

/* _roll_str() {{{2
 */
int
dice_roll_str(
    const char	*str)
{
	dice_t dice;

	dice_init(&dice, str);

	return dice_roll(&dice);
}

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
