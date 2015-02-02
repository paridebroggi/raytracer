#include <libft.h>
#include <rt.h>
#include <math.h>

void	paral_intersection(t_env *e, t_obj *paral, double dir[3], double o[3])
{
	double		eye[3];
	double		ray[3];
	double		k2;
	double		k1;

	vect_dup(eye, o);
	vect_dup(ray, dir);
	trasl_inv(eye, paral->c);
	rot_dir(eye, paral->sincos_inv);
	rot_dir(ray, paral->sincos_inv);
	if (ray[Z] < 1e-6 || ray[Z] > 1e-6)
		paral->dist = -eye[Z] / ray[Z];
	else
		paral->dist = -1.0;
	if (paral->dist > 1e-6)
	{
		get_inters_coord(e->eye, dir, paral->dist, paral->inters);
		trasl_inv(paral->inters, paral->c);
		rot_dir(paral->inters, paral->sincos_inv);
		k2 = (paral->c[X] * paral->inters[Y] - paral->inters[X] * paral->c[Y]) /
		(paral->cc[Y] * paral->c[X] - paral->c[Y] * paral->cc[X]);
		k1 = (paral->inters[X] - k2 * paral->cc[X]) / paral->c[X];
		if (k1 > 1.0 || k1 < 1e-1 || k2 > 1.0 || k2 < 1e-1)
			paral->dist = -1.0;
	}
}

void	paral_normal(t_obj *paral, double norm[3], double inters[3])
{
	(void)inters;
	norm[X] = 0;
	norm[Y] = 0;
	norm[Z] = 100;
	rot_dir(norm, paral->sincos);
}

void	get_paral(t_env *e, char **data)
{
	if (ft_tablen(data) != 17)
		fail(PARAM_PARAL);
	e->obj[e->n].c[X] = (double)atoi(data[1] + 2);
	e->obj[e->n].c[Y] = (double)atoi(data[2] + 2);
	e->obj[e->n].c[Z] = (double)atoi(data[3] + 2);
	e->obj[e->n].cc[X] = (double)atoi(data[4] + 2);
	e->obj[e->n].cc[Y] = (double)atoi(data[5] + 2);
	e->obj[e->n].cc[Z] = (double)atoi(data[6] + 2);
	e->obj[e->n].rot[X] = (double)atoi(data[7] + 6) * (M_PI / 180);
	e->obj[e->n].rot[Y] = (double)atoi(data[8] + 6) * (M_PI / 180);
	e->obj[e->n].rot[Z] = (double)atoi(data[9] + 6) * (M_PI / 180);
	calc_trigonometry(e->obj[e->n].sincos_inv, e->obj[e->n].rot, INV);
	calc_trigonometry(e->obj[e->n].sincos, e->obj[e->n].rot, DIR);
	e->obj[e->n].col.comp[B] = atoi(data[10] + 6);
	e->obj[e->n].col.comp[G] = atoi(data[11] + 6);
	e->obj[e->n].col.comp[R] = atoi(data[12] + 6);
	e->obj[e->n].bright = (double)atoi(data[13] + 7) * 0.1;
	e->obj[e->n].chessboard = atoi(data[16] + 14);
	e->obj[e->n].reflex = (double)atoi(data[15] + 7) * 0.1;
	e->obj[e->n].trans = (double)atoi(data[16] + 6) * 0.1;
	e->obj[e->n].calc_inters = paral_intersection;
	e->obj[e->n].calc_norm = paral_normal;
	e->n++;
}
