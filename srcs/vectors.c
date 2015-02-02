#include <rt.h>
#include <math.h>

double			vect_dotprod(double v[3], double u[3])
{
	return (v[X] * u[X] + v[Y] * u[Y] + v[Z] * u[Z]);
}

void			vect_crossprod(double v[3], double u[3], double result[3])
{
	result[X] = v[Y] * u[Z] - v[Z] * u[Y];
	result[Y] = v[Z] * u[X] - v[X] * u[Z];
	result[Z] = v[X] * u[Y] - v[Y] * u[X];
}

void			vect_dup(double v[3], double u[3])
{
	v[X] = u[X];
	v[Y] = u[Y];
	v[Z] = u[Z];
}

void			vect_norm(double v[3])
{
	double mag;

	mag = sqrt(v[X] * v[X] + v[Y] * v[Y] + v[Z] * v[Z]);
	v[X] /= mag;
	v[Y] /= mag;
	v[Z] /= mag;
}

double			vect_cos(double norm[3], double ray[3])
{
	double angle;

	angle = vect_dotprod(norm, ray)
		/ (sqrt(norm[X] * norm[X] + norm[Y] * norm[Y] + norm[Z] * norm[Z])
		* sqrt(ray[X] * ray[X] + ray[Y] * ray[Y] + ray[Z] * ray[Z]));
	return (angle);
}
