#include <libft.h>
#include <rt.h>
#include <math.h>

void	triangle_check(double k[2], t_obj *triangle)
{
	if (k[0] > 1.0 || k[0] < 1e-1 || k[1] > 1.0 || k[1] < 1e-1
		|| k[0] + k[1] >= 1.0)
		triangle->dist = -1.0;
}

void	triangle_intersection(t_env *e, t_obj *triangle, \
									double dir[3], double o[3])
{
	double		eye[3];
	double		ray[3];
	double		k[2];

	vect_dup(eye, o);
	vect_dup(ray, dir);
	trasl_inv(eye, triangle->c);
	rot_dir(eye, triangle->sincos_inv);
	rot_dir(ray, triangle->sincos_inv);
	if (ray[Z] < 1e-6 || ray[Z] > 1e-6)
		triangle->dist = -eye[Z] / ray[Z];
	else
		triangle->dist = -1.0;
	if (triangle->dist > 1e-6)
	{
		get_inters_coord(e->eye, dir, triangle->dist, triangle->inters);
		trasl_inv(triangle->inters, triangle->c);
		rot_dir(triangle->inters, triangle->sincos_inv);
		k[0] = (triangle->c[X] * triangle->inters[Y] - triangle->inters[X]
		* triangle->c[Y]) / (triangle->cc[Y] * triangle->c[X]
		- triangle->c[Y] * triangle->cc[X]);
		k[1] = (triangle->inters[X] - k[0] * triangle->cc[X]) / triangle->c[X];
		triangle_check(k, triangle);
	}
}

void	triangle_normal(t_obj *triangle, double norm[3], double inters[3])
{
	(void)inters;
	norm[X] = 0;
	norm[Y] = 0;
	norm[Z] = 100;
	rot_dir(norm, triangle->sincos);
}

void	get_triangle(t_env *e, char **data)
{
	if (ft_tablen(data) != 17)
		fail(PARAM_TRIANGLE);
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
	e->obj[e->n].calc_inters = triangle_intersection;
	e->obj[e->n].calc_norm = triangle_normal;
	e->n++;
}
