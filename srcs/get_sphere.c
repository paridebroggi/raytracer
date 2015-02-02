#include <math.h>
#include <libft.h>
#include <rt.h>

void	sphere_intersection(t_env *e, t_obj *sphere, double dir[3], double o[3])
{
	double		var[4];
	double		eye[3];
	double		ray[3];

	vect_dup(eye, o);
	vect_dup(ray, dir);
	trasl_inv(eye, sphere->c);
	var[F] = pow(ray[X], 2) + pow(ray[Y], 2) + pow(ray[Z], 2);
	var[S] = 2 * (ray[X] * eye[X] + ray[Y] * eye[Y] + ray[Z] * eye[Z]);
	var[T] = pow(eye[X], 2) + pow(eye[Y], 2)
			+ pow(eye[Z], 2) - pow(sphere->r, 2);
	var[DELTA] = pow(var[S], 2) - 4 * var[F] * var[T];
	solve_equation(sphere, var);
	if (sphere->cut == 1)
	{
		get_inters_coord(e->eye, dir, sphere->dist, sphere->inters);
		trasl_inv(sphere->inters, sphere->c);
		rot_dir(sphere->inters, sphere->sincos_inv);
		if (sphere->inters[Z] > sphere->r / 2)
			sphere->dist = -1;
	}
}

void	sphere_normal(t_obj *sphere, double norm[3], double inters[3])
{
	vect_dup(norm, inters);
	trasl_inv(norm, sphere->c);
}

void	get_sphere(t_env *e, char **data)
{
	if (ft_tablen(data) != 15)
		fail(PARAM_SPHERE);
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
	e->obj[e->n].cut = atoi(data[12] + 4);
	e->obj[e->n].reflex = (double)atoi(data[13] + 7) * 0.1;
	e->obj[e->n].trans = (double)atoi(data[14] + 6) * 0.1;
	e->obj[e->n].calc_inters = sphere_intersection;
	e->obj[e->n].calc_norm = sphere_normal;
	e->n++;
}
