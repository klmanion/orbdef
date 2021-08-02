/** shell.c
 */

#include "shell.h"

#include <ncurses.h>
#include <string.h>
#include <assert.h>
#include <err.h>

static	char *shell0[] =
	    {	/* shell 0 */
		"o",
		"\0"
	    };

static	char *shell1[] =
	    {	/* shell 1 */
		"/-\\",
		"| |",
		"\\-/",
		"\0"
	    };

static	char *shell2[] =
	    {	/* shell 2 */
		" /-----\\ ",
		"/       \\",
		"|       |",
		"\\       /",
		" \\-----/ ",
		"\0"
	    };

static	char *shell3[] =
	    {	/* shell 3 */
		"  /-------\\  ",
		" /         \\ ",
		"/           \\",
		"|           |",
		"|           |",
		"|           |",
		"\\           /",
		" \\         / ",
		"  \\-------/  ",
		"\0"
	    };

static	char **tab[] = { shell0, shell1, shell2, shell3 };

/* memory allocation {{{1 */
/* _alloc() {{{2
 * 	Allocate memory for a Shell struct.
 * 	Shall be freed by shell_free().
 */
shell_t*
shell_alloc(
    shell_t **ptr)
{
	shell_t *shell;

	shell = (shell_t *)malloc(sizeof(struct Shell));
	if (!shell)
	    errx(1,"malloc failure, %s:%d", __FILE__, __LINE__);

	return ptr? (*ptr=shell) : shell;
}

/* _init() {{{2
 * 	Initiallize the memory of the Shell struct.
 * 	Will allocate memory if passed NULL.
 * 	Returns a pointer to the Shell struct.
 */
shell_t*
shell_init(
    shell_t *shell)
{
	if (!shell)
	    shell = shell_alloc(NULL);

	shell->radius = 0;

	return shell;
}

/* _deinit() {{{2
 * 	Deinitialize the memory of the Shell struct.
 * 	Automatically called by _free().
 * 	Must be called on an statically allocated instance.
 */
shell_t*
shell_deinit(
    shell_t	*shell)
{
	assert (shell);

	/* TODO */

	return shell;
}

/* _free() {{{2
 * 	Free memory of a Shell struct pointer.
 * 	Automatically calls _deinit().
 */
shell_t*
shell_free(
    shell_t	**ptr)
{
	assert (ptr);

	free(shell_deinit(*ptr));

	return *ptr = (shell_t *)NULL;
}

/* _draw() {{{1
 */
void
shell_draw(
    const shell_t *const	s,
    const int			y,
    const int			x)
{
	int h,w,yoff,xoff;
	char **img;

	assert (s);

	img = tab[s->radius];

	for (h=0; *img[++h]; ) { }
	w = strlen(*img);

	yoff = -((h-1) / 2);
	xoff = -((w-1) / 2);

	for (int row=0; row<h; ++row)
	    for (int col=0; col<w; ++col)
		if (img[row][col] != ' ')
		    mvaddch(y+yoff+row, x+xoff+col, img[row][col]);
}

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
