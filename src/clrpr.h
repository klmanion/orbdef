/** clrpr.h: color pairs
 * Defines macroes for color attributes.
 */

#define CLRPR_WHITE 0
#define CLRPR_DEFAULT CLRPR_WHITE
#define CLRPR_RED 1
#define CLRPR_ENEMY CLRPR_RED
#define CLRPR_BROWN 2
#define CLRPR_BLUE 3
#define CLRPR_GREEN 4
#define CLRPR_MAGENTA 5

#define CLRPR_SELECT_TARGET 6
#define CLRPR_SELECT_FRIEND 7
#define CLRPR_SELECT_ENEMY 8
#define CLRPR_SELECT_SQUAD 9
#define CLRPR_SELECT_ITEM 10

#define CLR(x) COLOR_PAIR(CLRPR_ ## x)

/* vi: set ts=8 sw=8 noexpandtab tw=79: */
