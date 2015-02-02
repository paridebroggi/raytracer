#include <stdlib.h>
#include <math.h>
#include <rt.h>
#include <libft.h>

void	cone_intersection(t_env *e, t_obj *cone, double dir[3], double orig[3])
{
	double		var[4];
	double		eye[3];
	double		ray[3];

	vect_dup(eye, orig);
	vect_dup(ray, dir);
	trasl_inv(eye, cone->c);
	rot_dir(eye, cone->sincos_inv);
	rot_dir(ray, cone->sincos_inv);
	var[F] = pow(ray[X], 2) + pow(ray[Y], 2) - cone->a * pow(ray[Z], 2);
	var[S] = 2 * (ray[X] * eye[X] + ray[Y] * eye[Y]
			- cone->a * ray[Z] * eye[Z]);
	var[T] = pow(eye[X], 2) + pow(eye[Y], 2) - cone->a * pow(eye[Z], 2);
	var[DELTA] = pow(var[S], 2) - (4 * var[F] * var[T]);
	solve_equation(cone, var);
	if (cone->h > 1e-6)
	{
		get_inters_coord(e->eye, dir, cone->dist, cone->inters);
		trasl_inv(cone->inters, cone->c);
		rot_dir(cone->inters, cone->sincos_inv);
		if (abs(cone->inters[Z]) > cone->h || cone->inters[Z] > 1e-6)
			cone->dist = -1;
	}
}

void	cone_normal(t_obj *cone, double norm[3], double inters[3])
{
	vect_dup(norm, inters);
	trasl_inv(norm, cone->c);
	rot_dir(norm, cone->sincos_inv);
	norm[Z] = -(cone->a * norm[Z]);
	rot_dir(norm, cone->sincos);
}

void	get_cone(t_env *e, char **data)
{
	if (ft_tablen(data) != 15)
		fail(PARAM_CONE);
	e->obj[e->n].c[X] = (double)atoi(data[1] + 2);
	e->obj[e->n].c[Y] = (double)atoi(data[2] + 2);
	e->obj[e->n].c[Z] = (double)atoi(data[3] + 2);
	e->obj[e->n].rot[X] = (double)atoi(data[4] + 6) * (M_PI / 180);
	e->obj[e->n].rot[Y] = (double)atoi(data[5] + 6) * (M_PI / 180);
	e->obj[e->n].rot[Z] = (double)atoi(data[6] + 6) * (M_PI / 180);
	calc_trigonometry(e->obj[e->n].sincos_inv, e->obj[e->n].rot, INV);
	calc_trigonometry(e->obj[e->n].sincos, e->obj[e->n].rot, DIR);
	e->obj[e->n].h = (double)atoi(data[7] + 7);
	e->obj[e->n].a = tan((double)atoi(data[8] + 6) * M_PI / 180);
	e->obj[e->n].col.comp[B] = atoi(data[9] + 6);
	e->obj[e->n].col.comp[G] = atoi(data[10] + 6);
	e->obj[e->n].col.comp[R] = atoi(data[11] + 6);
	e->obj[e->n].bright = (double)atoi(data[12] + 7) * 0.1;
	e->obj[e->n].reflex = (double)atoi(data[13] + 7) * 0.1;
	e->obj[e->n].trans = (double)atoi(data[14] + 6) * 0.1;
	e->obj[e->n].calc_norm = cone_normal;
	e->obj[e->n].calc_inters = cone_intersection;
	e->n++;
}
