#include <libft.h>
#include <rt.h>
#include <math.h>

void	disc_intersection(t_env *e, t_obj *disc, double dir[3], double o[3])
{
	double		eye[3];
	double		ray[3];

	(void)e;
	vect_dup(eye, o);
	vect_dup(ray, dir);
	trasl_inv(eye, disc->c);
	rot_dir(eye, disc->sincos_inv);
	rot_dir(ray, disc->sincos_inv);
	if (ray[Z] < 1e-6 || ray[Z] > 1e-6)
		disc->dist = -eye[Z] / ray[Z];
	else
		disc->dist = -1.0;
	if (disc->dist > 1e-6)
	{
		get_inters_coord(e->eye, dir, disc->dist, disc->inters);
		trasl_inv(disc->inters, disc->c);
		rot_dir(disc->inters, disc->sincos_inv);
		if (pow(disc->inters[X], 2) + pow(disc->inters[Y], 2) > pow(disc->r, 2))
			disc->dist = -1.0;
	}
}

void	disc_normal(t_obj *disc, double norm[3], double inters[3])
{
	(void)inters;
	norm[X] = 0;
	norm[Y] = 0;
	norm[Z] = 100;
	rot_dir(norm, disc->sincos);
}

void	get_disc(t_env *e, char **data)
{
	if (ft_tablen(data) != 15)
		fail(PARAM_DISC);
	e->obj[e->n].c[X] = (double)atoi(data[1] + 2);
	e->obj[e->n].c[Y] = (double)atoi(data[2] + 2);
	e->obj[e->n].c[Z] = (double)atoi(data[3] + 2);
	e->obj[e->n].rot[X] = (double)atoi(data[4] + 6) * (M_PI / 180);
	e->obj[e->n].rot[Y] = (double)atoi(data[5] + 6) * (M_PI / 180);
	e->obj[e->n].rot[Z] = (double)atoi(data[6] + 6) * (M_PI / 180);
	calc_trigonometry(e->obj[e->n].sincos_inv, e->obj[e->n].rot, INV);
	calc_trigonometry(e->obj[e->n].sincos, e->obj[e->n].rot, DIR);
	e->obj[e->n].r = (double)atoi(data[7] + 7);
	e->obj[e->n].col.comp[B] = atoi(data[8] + 6);
	e->obj[e->n].col.comp[G] = atoi(data[9] + 6);
	e->obj[e->n].col.comp[R] = atoi(data[10] + 6);
	e->obj[e->n].bright = (double)atoi(data[11] + 7) * 0.1;
	e->obj[e->n].chessboard = atoi(data[12] + 11);
	e->obj[e->n].reflex = (double)atoi(data[13] + 7) * 0.1;
	e->obj[e->n].trans = (double)atoi(data[14] + 6) * 0.1;
	e->obj[e->n].calc_inters = disc_intersection;
	e->obj[e->n].calc_norm = disc_normal;
	e->n++;
}
