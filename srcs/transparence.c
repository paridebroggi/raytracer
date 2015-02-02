#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <rt.h>

void		get_transparence_ray(t_env *e, double ray[3], double coeff)
{
	double	norm[3];
	double	copy_ray[3];
	double	dotp;
	double	arg;

	vect_dup(norm, e->norm);
	vect_dup(copy_ray, ray);
	vect_norm(norm);
	vect_norm(copy_ray);
	dotp = vect_dotprod(copy_ray, norm);
	arg = 1 + pow(coeff, 2) * (pow(dotp, 2) - 1);
	if (arg < 1e-6)
		arg = 1e-6;
	e->t_ray[X] = coeff * copy_ray[X] + (coeff * dotp - sqrt(arg)) * norm[X];
	e->t_ray[Y] = coeff * copy_ray[Y] + (coeff * dotp - sqrt(arg)) * norm[Y];
	e->t_ray[Z] = coeff * copy_ray[Z] + (coeff * dotp - sqrt(arg)) * norm[Z];
}

void		get_transparence_color(t_env *e, double *dist_min, size_t n)
{
	t_obj	*obj;

	obj = &e->obj[n];
	if (obj->dist > 1e-6 && obj->dist < *dist_min)
	{
		*dist_min = obj->dist;
		e->nearest = n;
		if (obj->chessboard > 0)
		{
			texture_dispatcher(e, obj);
			e->pxcol = e->tmpcol;
		}
		else
			e->pxcol = obj->col;
	}
}

void		cast_transparence_rays(t_env *e, int loop, double first_coeff)
{
	double	dist_min;
	double	second_coeff;
	size_t	n;

	n = 0;
	second_coeff = e->obj[e->nearest].trans;
	dist_min = FLT_MAX;
	get_transparence_ray(e, e->p_ray, first_coeff / second_coeff);
	while (n < e->n)
	{
		e->obj[n].calc_inters(e, &e->obj[n], e->t_ray, e->inters);
		get_transparence_color(e, &dist_min, n);
		n++;
	}
	if (e->obj[e->nearest].trans > 1e-6 && loop < 3)
	{
		get_inters_coord(e->eye, e->p_ray, e->obj[e->nearest].dist, e->inters);
		vect_dup(e->eye, e->inters);
		vect_dup(e->p_ray, e->t_ray);
		e->obj[e->nearest].calc_norm(&e->obj[e->nearest], e->norm, e->inters);
		cast_transparence_rays(e, loop + 1, second_coeff);
	}
}

void		transparence(t_env *e, t_obj *obj)
{
	t_env	copy;
	double	k;
	double	k_inv;

	copy = *e;
	copy.pxcol.num = 0;
	cast_transparence_rays(&copy, 1, 1.0);
	k = obj->trans;
	k_inv = 1.0 - k;
	e->tmpcol.comp[B] = copy.pxcol.comp[B] * k + obj->col.comp[B] * k_inv;
	e->tmpcol.comp[G] = copy.pxcol.comp[G] * k + obj->col.comp[G] * k_inv;
	e->tmpcol.comp[R] = copy.pxcol.comp[R] * k + obj->col.comp[R] * k_inv;
}
