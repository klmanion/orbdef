/** type.c
 */

#include "type.h"

#include <assert.h>
#include <err.h>

/* _is_unit() {{{1
 */
bool
type_is_unit(
    const type_t	t)
{
	return t < 6;
}

/* _is_building() {{{1
 */
bool
type_is_building(
    const type_t	t)
{
	return t >= 6 && t < 14;
}

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
