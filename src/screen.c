/** screen.c
 */

#include "screen.h"

#include <assert.h>
#include <err.h>


/* memory allocation {{{1 */
/* _alloc() {{{2
 * 	Allocate memory for a Screen struct.
 * 	Shall be freed by screen_free().
 */
screen_t*
screen_alloc(
    screen_t **ptr)
{
	screen_t *screen;

	screen = (screen_t *)malloc(sizeof(struct Screen));
	if (!screen)
	    errx(1,"malloc failure, %s:%d", __FILE__, __LINE__);

	return ptr? (*ptr=screen) : screen;
}

/* _init() {{{2
 * 	Initiallize the memory of the Screen struct.
 * 	Will allocate memory if passed NULL.
 * 	Returns a pointer to the Screen struct.
 */
screen_t*
screen_init(
    screen_t		*screen,
    screen_data_t	 data,
    screen_funct_t	 run)
{
	if (!screen)
	    screen = screen_alloc(NULL);

	screen->data = data;
	screen->run = run;

	return screen;
}

/* _deinit() {{{2
 * 	Deinitialize the memory of the Screen struct.
 * 	Automatically called by _free().
 * 	Must be called on an statically allocated instance.
 */
screen_t*
screen_deinit(
    screen_t	*screen)
{
	assert (screen);

	/* whether data is manually or statically allocated,
	 * and, thereby, whether it should be freed,
	 * shall be up to the creator of this struct. */

	return screen;
}

/* _free() {{{2
 * 	Free memory of a Screen struct pointer.
 * 	Automatically calls _deinit().
 */
screen_t*
screen_free(
    screen_t	**ptr)
{
	assert (ptr);

	free(screen_deinit(*ptr));

	return *ptr = (screen_t *)NULL;
}

/* _run() {{{1
 */
screen_t*
screen_run(
    screen_t	*scr,
    void	*vptr)
{
	return scr->run(scr, vptr);
}

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
