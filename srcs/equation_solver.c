#include <libft.h>
#include <rt.h>
#include <math.h>

void			solve_equation(t_obj *obj, double var[4])
{
	double		solution1;
	double		solution2;

	obj->dist = -1.0;
	if (var[DELTA] >= 1e-6)
	{
		solution1 = (-var[S] + sqrt(var[DELTA])) / (2 * var[F]);
		solution2 = (-var[S] - sqrt(var[DELTA])) / (2 * var[F]);
		if (solution1 > 1e-6 && solution2 > 1e-6)
			obj->dist = solution1 < solution2 ? solution1 : solution2;
		else if (solution1 > 1e-6 || solution2 > 1e-6)
			obj->dist = solution1 > 1e-6 ? solution1 : solution2;
	}
}
