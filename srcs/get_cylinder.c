#include <stdlib.h>
#include <math.h>
#include <libft.h>
#include <rt.h>

void	cyl_intersection(t_env *e, t_obj *cyl, double dir[3], double orig[3])
{
	double		var[4];
	double		eye[3];
	double		ray[3];

	vect_dup(eye, orig);
	vect_dup(ray, dir);
	trasl_inv(eye, cyl->c);
	rot_dir(eye, cyl->sincos_inv);
	rot_dir(ray, cyl->sincos_inv);
	var[F] = pow(ray[X], 2) + pow(ray[Y], 2);
	var[S] = 2 * (ray[X] * eye[X] + ray[Y] * eye[Y]);
	var[T] = pow(eye[X], 2) + pow(eye[Y], 2) - pow(cyl->r, 2);
	var[DELTA] = pow(var[S], 2) - 4 * var[F] * var[T];
	solve_equation(cyl, var);
	if (cyl->h > 1e-6)
	{
		get_inters_coord(e->eye, dir, cyl->dist, cyl->inters);
		trasl_inv(cyl->inters, cyl->c);
		rot_dir(cyl->inters, cyl->sincos_inv);
		if (abs(cyl->inters[Z]) > cyl->h / 2)
			cyl->dist = -1;
	}
}

void	cyl_normal(t_obj *cyl, double norm[3], double inters[3])
{
	vect_dup(norm, inters);
	trasl_inv(norm, cyl->c);
	rot_dir(norm, cyl->sincos_inv);
	norm[Z] = 0.0f;
	rot_dir(norm, cyl->sincos);
}

void	get_cyl(t_env *e, char **data)
{
	if (ft_tablen(data) != 15)
		fail(PARAM_CYL);
	e->obj[e->n].c[X] = (double)atoi(data[1] + 2);
	e->obj[e->n].c[Y] = (double)atoi(data[2] + 2);
	e->obj[e->n].c[Z] = (double)atoi(data[3] + 2);
	e->obj[e->n].rot[X] = (double)atoi(data[4] + 6) * (M_PI / 180);
	e->obj[e->n].rot[Y] = (double)atoi(data[5] + 6) * (M_PI / 180);
	e->obj[e->n].rot[Z] = (double)atoi(data[6] + 6) * (M_PI / 180);
	calc_trigonometry(e->obj[e->n].sincos_inv, e->obj[e->n].rot, INV);
	calc_trigonometry(e->obj[e->n].sincos, e->obj[e->n].rot, DIR);
	e->obj[e->n].r = (double)atoi(data[7] + 7);
	e->obj[e->n].h = (double)atoi(data[8] + 7);
	e->obj[e->n].col.comp[B] = atoi(data[9] + 6);
	e->obj[e->n].col.comp[G] = atoi(data[10] + 6);
	e->obj[e->n].col.comp[R] = atoi(data[11] + 6);
	e->obj[e->n].bright = (double)atoi(data[12] + 7) * 0.1;
	e->obj[e->n].reflex = (double)atoi(data[13] + 6) * 0.1;
	e->obj[e->n].trans = (double)atoi(data[14] + 6) * 0.1;
	e->obj[e->n].calc_inters = cyl_intersection;
	e->obj[e->n].calc_norm = cyl_normal;
	e->n++;
}
