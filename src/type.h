/** type.h
 */

#ifndef _TYPE_H_
#define _TYPE_H_

#include <stdlib.h>
#include <stdbool.h>

typedef
enum __attribute__((packed)) Type
{
	chum=0,
	soldier,
	medic,
	architech,
	mage,
	seige,

	tower=6,
	town,
	raze,
	trench,
	fortification,
	fence,
	road,
	mine,

	item=14
} type_t;

bool	type_is_unit (const type_t);
bool	type_is_building (const type_t);

#endif /* !_TYPE_H_ */

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
