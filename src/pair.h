/** pair.h
 */

#ifndef _PAIR_H_
#define _PAIR_H_

#include <stdlib.h>
#include <sys/queue.h>

typedef
struct Pair
{
	void			*car;
	STAILQ_ENTRY(Pair)	 cdr;
} pair_t;

typedef	STAILQ_HEAD(Head, Pair) head_t;

pair_t*	pair_alloc (pair_t **);
pair_t*	pair_init (pair_t *);
pair_t*	pair_init_car (pair_t *,void *);
pair_t*	pair_deinit (pair_t *);
pair_t*	pair_free (pair_t **);

#endif /* !_PAIR_H_ */

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
