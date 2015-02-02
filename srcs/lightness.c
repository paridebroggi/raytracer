#include <math.h>
#include <rt.h>

/*
** light = ambiance + diffusion + specular (phong algorithm)
*/
void		lightness(t_env *e, t_obj *obj, t_light *spot)
{
	double		angle;
	double		omega;

	e->intcol.b += spot->col.comp[B] * e->amb_light;
	e->intcol.g += spot->col.comp[G] * e->amb_light;
	e->intcol.r += spot->col.comp[R] * e->amb_light;
	angle = vect_cos(e->norm, e->s_ray);
	omega = vect_cos(e->norm, e->r_ray) + 0.001;
	if (angle > 1e-6)
	{
		e->intcol.b += e->tmpcol.comp[B] * angle;
		e->intcol.g += e->tmpcol.comp[G] * angle;
		e->intcol.r += e->tmpcol.comp[R] * angle;
	}
	e->intcol.b += obj->bright * spot->col.comp[B] * pow(omega, 1000);
	e->intcol.g += obj->bright * spot->col.comp[G] * pow(omega, 1000);
	e->intcol.r += obj->bright * spot->col.comp[R] * pow(omega, 1000);
}
