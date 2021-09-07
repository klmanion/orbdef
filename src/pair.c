/** pair.c
 */

#include "pair.h"

#include <assert.h>
#include <err.h>

/* memory allocation {{{1 */
/* _alloc() {{{2
 * 	Allocate memory for a Pair struct.
 * 	Shall be freed by pair_free().
 */
pair_t*
pair_alloc(
    pair_t **ptr)
{
	pair_t *pair;

	pair = (pair_t *)malloc(sizeof(struct Pair));
	if (!pair)
	    errx(1,"malloc failure, %s:%d", __FILE__, __LINE__);

	return ptr? (*ptr=pair) : pair;
}

/* _init() {{{2
 * 	Initiallize the memory of the Pair struct.
 * 	Will allocate memory if passed NULL.
 * 	Returns a pointer to the Pair struct.
 */
pair_t*
pair_init(
    pair_t *pair)
{
	if (!pair)
	    pair = pair_alloc(NULL);

	pair->car = NULL;
	STAILQ_NEXT(pair, cdr) = NULL;

	return pair;
}

/* _init_car() {{{2
 * 	Initialize memory of Pair struct with its car element.
 */
pair_t*
pair_init_car(
    pair_t	*pair,
    void	*car)
{
	pair = pair_init(NULL);

	pair->car = car;

	return pair;
}

/* _deinit() {{{2
 * 	Deinitialize the memory of the Pair struct.
 * 	Automatically called by _free().
 * 	Must be called on an statically allocated instance.
 */
pair_t*
pair_deinit(
    pair_t	*pair)
{
	assert (pair);

	/* TODO */

	return pair;
}

/* _free() {{{2
 * 	Free memory of a Pair struct pointer.
 * 	Automatically calls _deinit().
 */
pair_t*
pair_free(
    pair_t	**ptr)
{
	assert (ptr);

	free(pair_deinit(*ptr));

	return *ptr = (pair_t *)NULL;
}

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
