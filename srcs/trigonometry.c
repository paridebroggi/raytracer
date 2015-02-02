#include <math.h>
#include <rt.h>

void			calc_trigonometry(double sincos[6], double angle[3], int flag)
{
	if (flag == DIR)
	{
		sincos[SX] = sin(angle[X]);
		sincos[SY] = sin(angle[Y]);
		sincos[SZ] = sin(angle[Z]);
		sincos[CX] = cos(angle[X]);
		sincos[CY] = cos(angle[Y]);
		sincos[CZ] = cos(angle[Z]);
	}
	else
	{
		sincos[SX] = sin(-angle[X]);
		sincos[SY] = sin(-angle[Y]);
		sincos[SZ] = sin(-angle[Z]);
		sincos[CX] = cos(-angle[X]);
		sincos[CY] = cos(-angle[Y]);
		sincos[CZ] = cos(-angle[Z]);
	}
}
