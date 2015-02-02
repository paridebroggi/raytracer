#include <libft.h>
#include <rt.h>
#include <math.h>

void	plane_intersection(t_env *e, t_obj *plane, double dir[3], double o[3])
{
	double		eye[3];
	double		ray[3];

	(void)e;
	vect_dup(eye, o);
	vect_dup(ray, dir);
	trasl_inv(eye, plane->c);
	rot_dir(eye, plane->sincos_inv);
	rot_dir(ray, plane->sincos_inv);
	if (ray[Z] < 1e-6 || ray[Z] > 1e-6)
		plane->dist = -eye[Z] / ray[Z];
	else
		plane->dist = -1.0;
}

void	plane_normal(t_obj *plane, double norm[3], double inters[3])
{
	(void)inters;
	norm[X] = 0;
	norm[Y] = 0;
	norm[Z] = 100;
	rot_dir(norm, plane->sincos);
}

void	get_plane(t_env *e, char **data)
{
	if (ft_tablen(data) != 14)
		fail(PARAM_PLANE);
	e->obj[e->n].c[X] = (double)atoi(data[1] + 2);
	e->obj[e->n].c[Y] = (double)atoi(data[2] + 2);
	e->obj[e->n].c[Z] = (double)atoi(data[3] + 2);
	e->obj[e->n].rot[X] = (double)atoi(data[4] + 6) * (M_PI / 180);
	e->obj[e->n].rot[Y] = (double)atoi(data[5] + 6) * (M_PI / 180);
	e->obj[e->n].rot[Z] = (double)atoi(data[6] + 6) * (M_PI / 180);
	calc_trigonometry(e->obj[e->n].sincos_inv, e->obj[e->n].rot, INV);
	calc_trigonometry(e->obj[e->n].sincos, e->obj[e->n].rot, DIR);
	e->obj[e->n].col.comp[B] = atoi(data[7] + 6);
	e->obj[e->n].col.comp[G] = atoi(data[8] + 6);
	e->obj[e->n].col.comp[R] = atoi(data[9] + 6);
	e->obj[e->n].bright = (double)atoi(data[10] + 7) * 0.1;
	e->obj[e->n].chessboard = atoi(data[11] + 11);
	e->obj[e->n].reflex = (double)atoi(data[12] + 7) * 0.1;
	e->obj[e->n].trans = (double)atoi(data[13] + 6) * 0.1;
	e->obj[e->n].calc_inters = plane_intersection;
	e->obj[e->n].calc_norm = plane_normal;
	e->n++;
}
