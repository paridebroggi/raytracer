#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <rt.h>

void			get_reflexed_color(t_env *e, double *dist_min, size_t n)
{
	t_obj		*obj;

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

void			cast_reflex_rays(t_env *e, int loop)
{
	double		dist_min;
	size_t		n;

	n = 0;
	dist_min = FLT_MAX;
	get_reflexed_p_ray(e, e->p_ray);
	while (n < e->n)
	{
		e->obj[n].calc_inters(e, &e->obj[n], e->r_ray, e->inters);
		get_reflexed_color(e, &dist_min, n);
		n++;
	}
	if (e->obj[n].reflex == 1 && loop < 5)
	{
		vect_dup(e->eye, e->inters);
		vect_dup(e->p_ray, e->r_ray);
		cast_reflex_rays(e, loop + 1);
	}
}

void			reflexion(t_env *e, t_obj *obj)
{
	t_env		copy;
	double		k;
	double		k_inv;

	copy = *e;
	copy.pxcol.num = 0;
	cast_reflex_rays(&copy, 1);
	k = obj->reflex;
	k_inv = 1.0 - k;
	e->tmpcol.comp[B] = copy.pxcol.comp[B] * k + obj->col.comp[B] * k_inv;
	e->tmpcol.comp[G] = copy.pxcol.comp[G] * k + obj->col.comp[G] * k_inv;
	e->tmpcol.comp[R] = copy.pxcol.comp[R] * k + obj->col.comp[R] * k_inv;
}
