#include <rt.h>

void	get_primary_ray(t_env *e)
{
	e->p_ray[X] = e->mlx.w / 2 * e->mlx.fov;
	e->p_ray[Y] = e->mlx.w / 2 - e->pixel.x;
	e->p_ray[Z] = e->mlx.h / 2 - e->pixel.y;
	rot_dir(e->p_ray, e->sincos);
}

void	get_inters_coord(double eye[3], double ray[3], \
							double dist, double inters[3])
{
	inters[X] = eye[X] + ray[X] * dist;
	inters[Y] = eye[Y] + ray[Y] * dist;
	inters[Z] = eye[Z] + ray[Z] * dist;
}

void	get_secondary_ray(t_env *e, t_light *spot)
{
	e->s_ray[X] = spot->src[X] - e->inters[X];
	e->s_ray[Y] = spot->src[Y] - e->inters[Y];
	e->s_ray[Z] = spot->src[Z] - e->inters[Z];
}

void	get_reflexed_p_ray(t_env *e, double ray[3])
{
	double	norm[3];
	double	copy_ray[3];
	double	dotp;

	vect_dup(norm, e->norm);
	vect_dup(copy_ray, ray);
	vect_norm(norm);
	vect_norm(copy_ray);
	dotp = vect_dotprod(norm, copy_ray);
	e->r_ray[X] = -2 * norm[X] * dotp + copy_ray[X];
	e->r_ray[Y] = -2 * norm[Y] * dotp + copy_ray[Y];
	e->r_ray[Z] = -2 * norm[Z] * dotp + copy_ray[Z];
}

void	get_reflexed_s_ray(t_env *e, double ray[3])
{
	double	norm[3];
	double	copy_ray[3];
	double	dotp;

	vect_dup(norm, e->norm);
	vect_dup(copy_ray, ray);
	vect_norm(norm);
	vect_norm(copy_ray);
	dotp = vect_dotprod(norm, copy_ray);
	e->r_ray[X] = 2 * norm[X] * dotp + copy_ray[X];
	e->r_ray[Y] = 2 * norm[Y] * dotp + copy_ray[Y];
	e->r_ray[Z] = 2 * norm[Z] * dotp + copy_ray[Z];
}
