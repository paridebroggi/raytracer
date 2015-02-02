#include <rt.h>

void		init_vect(double v[3])
{
	v[X] = 0.0f;
	v[Y] = 0.0f;
	v[Z] = 0.0f;
}

void		init_obj(t_env *e)
{
	init_vect(e->obj[e->n].c);
	init_vect(e->obj[e->n].norm);
	init_vect(e->obj[e->n].inters);
	init_vect(e->obj[e->n].rot);
	init_vect(e->obj[e->n].sincos);
	init_vect(e->obj[e->n].sincos_inv);
	e->obj[e->n].r = 0.0f;
	e->obj[e->n].rr = 0.0f;
	e->obj[e->n].h = 0.0f;
	e->obj[e->n].a = 0.0f;
	e->obj[e->n].col.comp[B] = 0;
	e->obj[e->n].col.comp[G] = 0;
	e->obj[e->n].col.comp[R] = 0;
	e->obj[e->n].dist = 0.0f;
	e->obj[e->n].bright = 0.0f;
	e->obj[e->n].reflex = 0.0f;
	e->obj[e->n].trans = 0.0f;
	e->obj[e->n].type = 0;
	e->obj[e->n].cut = 0;
	e->obj[e->n].chessboard = 0;
	e->obj[e->n].calc_norm = NULL;
	e->obj[e->n].calc_inters = NULL;
}
