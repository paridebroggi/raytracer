#include <rt.h>

void		multi_spot_normalizer(t_env *e, t_intcol *col, size_t l)
{
	unsigned int	saturation;

	saturation = 255 * l;
	col->b = col->b > saturation ? saturation : col->b;
	col->g = col->g > saturation ? saturation : col->g;
	col->r = col->r > saturation ? saturation : col->r;
	e->pxcol.comp[B] = e->intcol.b / l;
	e->pxcol.comp[G] = e->intcol.g / l;
	e->pxcol.comp[R] = e->intcol.r / l;
}

void		get_temporary_color(t_env *e, t_obj *obj)
{
	if (obj->chessboard > 0)
		texture_dispatcher(e, obj);
	else
		e->tmpcol = obj->col;
	if (obj->reflex > 1e-6)
		reflexion(e, obj);
	if (obj->trans > 1e-6)
		transparence(e, obj);
}

void		get_color(t_env *e)
{
	size_t	l;
	t_obj	*obj;

	l = 0;
	e->intcol.b = 0;
	e->intcol.g = 0;
	e->intcol.r = 0;
	obj = &e->obj[e->nearest];
	get_inters_coord(e->eye, e->p_ray, obj->dist, e->inters);
	obj->calc_norm(obj, e->norm, e->inters);
	get_temporary_color(e, obj);
	while (l < e->l)
	{
		get_secondary_ray(e, &e->spot[l]);
		get_reflexed_s_ray(e, e->s_ray);
		lightness(e, &e->obj[e->nearest], &e->spot[l]);
		l++;
	}
	multi_spot_normalizer(e, &e->intcol, l);
	trace_shadows(e);
}
