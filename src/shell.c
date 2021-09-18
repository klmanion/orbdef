/** shell.c
 */

#include "shell.h"

#include <ncurses.h>
#include <string.h>
#include <assert.h>
#include <err.h>
#include "wall.h"

/* image table {{{1 */
static	char *shell0[] = {	/* shell 0 */
	"o",
	"\0"
};

static	char *shell1[] = {	/* shell 1 */
	"/-\\",
	"| |",
	"\\-/",
	"\0"
};

static	char *shell2[] = {	/* shell 2 */
	" /-----\\ ",
	"/       \\",
	"|       |",
	"\\       /",
	" \\-----/ ",
	"\0"
};

static	char *shell3[] = {	/* shell 3 */
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
    shell_t	*shell,
    const int	 radius,
    const int	 y,
    const int	 x)
{
	char **img;
	int w;
	int cols,rows;

	assert (radius >= 0 && radius <= 3);

	if (!shell)
	    shell = shell_alloc(NULL);

	entity_init(entity_alloc(&shell->e), y,x);

	shell->radius = radius;

	img = shell_image(shell);

	shell->wall_lst = (wall_t **)malloc(sizeof(wall_t *)
					   * shell_walls_num(shell));
	if (!shell->wall_lst)
	    errx(1,"malloc failure, %s:%d", __FILE__, __LINE__);

	w = 0;

	rows = shell_rows(shell);
	cols = shell_cols(shell);

	for (size_t i=0; i<rows; ++i)
	    {
		for (size_t j=0; j<cols; ++j)
		    {
			char tok;
			int yd,xd;

			if (img[i][j] == ' ')
			    continue;

			tok = img[i][j];

			/*
			 *  /-\
			 *  | |
			 *  \-/
			 *
			 *  o: 1,1	0,0
			 *  /: 0,0	-1,-1
			 *  -: 0,1	-1,0
			 *  |: 1,0	0,-1
			 */
			yd = i - (rows-1)/2;
			xd = j - (cols-1)/2;

			wall_init(wall_alloc(&shell->wall_lst[w++]),
				  tok,
				  shell->e->pos.yo,shell->e->pos.xo,
				  yd,xd);
		    }
	    }

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

/* accessors {{{1 */
/* _image() {{{2
 */
char**
shell_image(
    const shell_t *const	sh)
{
	assert (sh);
	return tab[sh->radius];
}

/* _rows() {{{2
 */
int
shell_rows(
    const shell_t *const	sh)
{
	char **img, **ptr;

	for (ptr=img=shell_image(sh); *ptr[0]; ++ptr) { }
	return ptr - img;
}

/* _cols() {{{2
 */
int
shell_cols(
    const shell_t *const	sh)
{
	return strlen(*shell_image(sh));
}

/* walls_num() {{{2
 */
int
shell_walls_num(
    const shell_t *const	sh)
{
	int acc;
	char **img;

	acc = 0;
	img = shell_image(sh);

	for (size_t i=0; i<shell_rows(sh); ++i)
	    for (size_t j=0; j<shell_cols(sh); ++j)
		if (img[i][j] != ' ')
		    ++acc;

	return acc;
}

/* drawing {{{1 */
/* _draw() {{{2
 */
void
shell_draw(
    const shell_t *const	sh)
{
	assert (sh);

	for (size_t w=0; w<shell_walls_num(sh); ++w)
	    {
		wall_t *wall;

		wall = sh->wall_lst[w];
		assert (wall);

		mvprintw(pos_y(&wall->e->pos),pos_x(&wall->e->pos),
			 "%c", wall->tok);
	    }

	return;
}

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
