#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int
main()
{
	/* calc possible ways to roll 3d6 */

	double sum_arr[16];	/* 3-18 -> 0-15 */
	double acc;

	memset(sum_arr, 0, 16);
	acc = 0;

	for (int d0=1; d0<=6; ++d0)
	    for (int d1=1; d1<=6; ++d1)
		for (int d2=1; d2<=6; ++d2)
		    sum_arr[(d0+d1+d2)-3] += 1;

	for (int num=3; num<=18; ++num)
	    {
		int dex = num-3;
		double per = sum_arr[dex]/pow(6,3);

		printf("%d:\t%.0lf\t%lf\t%lf\n",
		       num,
		       sum_arr[dex],
		       per,
		       (acc += per));
	    }

	return EXIT_SUCCESS;
}
