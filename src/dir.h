/** dir.h
 */

#ifndef _DIR_H_
#define _DIR_H_

#include <stdlib.h>
#include <stdbool.h>

typedef
enum dir
{
	dir_tl,	dir_top,	dir_tr,
	dir_cl,	dir_ctr,	dir_cr,
	dir_bl,	dir_bot,	dir_br
} dir_t;

bool	dir_is_center (const dir_t);
bool	dir_is_up (const dir_t);
bool	dir_is_down (const dir_t);
bool	dir_is_left (const dir_t);
bool	dir_is_right (const dir_t);

#endif /* !_DIR_H_ */

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
