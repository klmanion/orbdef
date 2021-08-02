/** soldier.h
 */

#ifndef _SOLDIER_H_
#define _SOLDIER_H_

#include <stdlib.h>
#include <stdbool.h>
#include "entity.h"
#include "stbl.h"
#include "dice.h"

typedef
enum Soldier_type
{
	undefined = 0,
	squire,
	knight,
	magician,
	medic,
	architech,
	special
} soldier_typ;

static	const char *basehp[] =
{
	"0",	/* undefined */
	"1",	/* squire */
	"d8",	/* knight */
	"d4",	/* magician */
	"d6",	/* medic */
	"3",	/* architecht */
	"-1"	/* special */
};

static	const char icon[] =
{
	'\0',	/* undefined */
	'o',	/* squire */
	'O',	/* knight */
	'0',	/* magician */
	'm',	/* medic */
	'9',	/* architect */
	'S'	/* special */
};

typedef
struct Soldier
{
	soldier_typ	styp;

	stbl_t		*stbl;
	int		 maxhp;
	int		 hp;	/* reffered in-game as `health' */

	bool	is_enemy;

	entity_t	*e;
} soldier_t;

soldier_t*	soldier_alloc (soldier_t **);
soldier_t*	soldier_init (soldier_t *,const soldier_typ,stbl_t *,const bool);
soldier_t*	soldier_deinit (soldier_t *);
soldier_t*	soldier_free (soldier_t **);

void	soldier_draw (const soldier_t *const);

#endif /* !_SOLDIER_H_ */

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
