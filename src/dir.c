/** dir.c
 */

#include "dir.h"

#include <assert.h>
#include <err.h>

/* _is_center()
 * 	Only true for being centered.
 * 	Facing center-left and center-right will prove false.
 */
bool
dir_is_center(
    const dir_t	dir)
{
	return dir == dir_ctr;
}

/* _is_up() {{{1
 */
bool
dir_is_up(
    const dir_t	dir)
{
	return dir == dir_tl
		|| dir == dir_top
		|| dir == dir_tr
		;
}

/* _is_down() {{{1
 */
bool
dir_is_down(
    const dir_t	dir)
{
	return dir == dir_bl
		|| dir == dir_bot
		|| dir == dir_br
		;
}

/* _is_left()
 */
bool
dir_is_left(
    const dir_t	dir)
{
	return dir == dir_tl
		|| dir == dir_cl
		|| dir == dir_bl
		;
}

/* _is_right()
 */
bool
dir_is_right(
    const dir_t	dir)
{
	return dir == dir_tr
		|| dir == dir_cr
		|| dir == dir_br
		;
}

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
