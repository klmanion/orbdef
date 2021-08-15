/** screen.h
 */

#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <stdlib.h>

typedef	void *	screen_data_t;
typedef struct Screen* (*screen_funct_t)(struct Screen *,void *);

typedef
struct Screen
{
	screen_data_t	data;	/* environment common among screens */
	screen_funct_t	run;
} screen_t;

screen_t*	screen_alloc (screen_t **);
screen_t*	screen_init (screen_t *,screen_data_t,screen_funct_t);
screen_t*	screen_deinit (screen_t *);
screen_t*	screen_free (screen_t **);

screen_t*	screen_run (screen_t *,void *);

#endif /* !_SCREEN_H_ */

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
