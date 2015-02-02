#include <math.h>
#include <rt.h>

/*
** rot x: y ---> z | rot y: z ---> x | rot z: x ---> y
*/
void		rot_dir(double vect[3], double v[6])
{
	double	tmp[3];

	vect_dup(tmp, vect);
	vect[X] = tmp[X] * v[CZ] * v[CY] - tmp[Y] * v[SZ] * v[CY] + tmp[Z] * v[SY];
	vect[Y] = tmp[X] * (v[CZ] * v[SY] * v[SX] + v[SZ] * v[CX])
				+ tmp[Y] * (v[CZ] * v[CX] - v[SZ] * v[SY] * v[SX])
				- tmp[Z] * v[CY] * v[SX];
	vect[Z] = tmp[X] * (v[SZ] * v[SX] - v[CZ] * v[SY] * v[CX])
				+ tmp[Y] * (v[SZ] * v[SY] * v[CX] + v[CZ] * v[SX])
				+ tmp[Z] * v[CY] * v[CX];
}

void		rot_inv(double vect[3], double v[6])
{
	double	tmp[3];

	vect_dup(tmp, vect);
	vect[X] = tmp[X] * v[CY] * v[CZ]
				+ tmp[Y] * (v[CX] * v[SZ] - v[SX] * v[SY] * v[CZ])
				+ tmp[Z] * (v[SX] * v[SZ] + v[CX] * v[SY] * v[CZ]);
	vect[Y] = tmp[X] * v[CY] * v[SZ]
				+ tmp[Y] * (v[CX] * v[CZ] + v[SX] * v[SY] * v[SZ])
				+ tmp[Z] * (v[CX] * v[SY] * v[SZ] - v[SX] * v[CZ]);
	vect[Z] = tmp[X] * -v[SY] - tmp[Y] * v[SX] * v[CY] + tmp[Z] * v[CX] * v[CY];
}

void		trasl_dir(double vect[3], double v[3])
{
	vect[X] += v[X];
	vect[Y] += v[Y];
	vect[Z] += v[Z];
}

void		trasl_inv(double vect[3], double v[3])
{
	vect[X] -= v[X];
	vect[Y] -= v[Y];
	vect[Z] -= v[Z];
}
