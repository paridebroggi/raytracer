#include <math.h>
#include <libft.h>
#include <rt.h>

void	torus_intersection(t_env *e, t_obj *torus, double dir[3], double o[3])
{
	double		var[5];
	double		eye[3];
	double		ray[3];

	(void)e;
	(void)var;
	vect_dup(eye, o);
	vect_dup(ray, dir);
	trasl_inv(eye, torus->c);
	rot_dir(eye, torus->sincos_inv);
	rot_dir(ray, torus->sincos_inv);
	var[4] = pow(vect_dotprod(ray, ray), 2);
	var[3] = 4 * vect_dotprod(ray, ray) * vect_dotprod(eye, ray);
	var[2] = 4 * pow(vect_dotprod(eye, ray), 2) + 2 * vect_dotprod(ray, ray)
			* (vect_dotprod(eye, eye) - pow(torus->r, 2) - pow(torus->rr, 2))
			+ 4 * pow(torus->rr, 2) * pow(ray[Z], 2);
	var[1] = 4 * vect_dotprod(eye, ray) * (vect_dotprod(eye, eye)
			- pow(torus->r, 2) - pow(torus->rr, 2)) + 8
			* pow(torus->rr, 2) * eye[Z] * ray[Z];
	var[0] = pow((vect_dotprod(eye, eye) - pow(torus->r, 2)
			- pow(torus->rr, 2)), 2) + 4 * pow(torus->rr, 2) * pow(eye[Z], 2)
			- 4 * pow(torus->rr, 2) * pow(torus->r, 2);
}

void	torus_normal(t_obj *torus, double norm[3], double inters[3])
{
	vect_dup(norm, inters);
	trasl_inv(norm, torus->c);
	rot_dir(norm, torus->sincos_inv);
	norm[Z] = 0.0f;
	rot_dir(norm, torus->sincos);
}

void	get_torus(t_env *e, char **data)
{
	if (ft_tablen(data) != 14)
		fail(PARAM_TORUS);
	e->obj[e->n].c[X] = (double)atoi(data[1] + 2);
	e->obj[e->n].c[Y] = (double)atoi(data[2] + 2);
	e->obj[e->n].c[Z] = (double)atoi(data[3] + 2);
	e->obj[e->n].rot[X] = (double)atoi(data[4] + 6) * (M_PI / 180);
	e->obj[e->n].rot[Y] = (double)atoi(data[5] + 6) * (M_PI / 180);
	e->obj[e->n].rot[Z] = (double)atoi(data[6] + 6) * (M_PI / 180);
	calc_trigonometry(e->obj[e->n].sincos_inv, e->obj[e->n].rot, INV);
	calc_trigonometry(e->obj[e->n].sincos, e->obj[e->n].rot, DIR);
	e->obj[e->n].r = (double)atoi(data[7] + 7);
	e->obj[e->n].rr = (double)atoi(data[8] + 7);
	e->obj[e->n].col.comp[B] = atoi(data[9] + 6);
	e->obj[e->n].col.comp[G] = atoi(data[10] + 6);
	e->obj[e->n].col.comp[R] = atoi(data[11] + 6);
	e->obj[e->n].bright = (double)atoi(data[12] + 7) * 0.1;
	e->obj[e->n].reflex = atoi(data[13] + 7);
	e->obj[e->n].calc_inters = torus_intersection;
	e->obj[e->n].calc_norm = torus_normal;
	e->n++;
}
