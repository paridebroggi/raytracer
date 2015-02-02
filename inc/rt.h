#ifndef RT_H
# define RT_H

# include <stddef.h>
# include <rt_structs.h>
# include <rt_defines.h>

/*
** get_scene_data.c
*/
void			get_scene(t_env *e, char *arg);

/*
** get_window_info.c
*/
void			get_window(t_env *e, char **data);
void			get_eye(t_env *e, char **data);
void			get_sphere(t_env *e, char **data);

/*
** init_struct.c
*/
void			init_obj(t_env *e);

/*
** raytracer.c
*/
void			raytracer(t_env *e);

/*
** loading_bar.c
*/
void			end_curses(void);
void			init_ncurses(int *h, int *w);
void			loading_percentage(t_env *e, int h, int w);

/*
** usage_fail.c
*/
void			fail(int err);
void			usage(void);

/*
** mlx.c
*/
void			init_mlx(t_mlx *mlx);
void			show_final_window(t_mlx *mlx);
int				expose_handler(t_mlx *mlx);
int				key_hook_handler(int keycode, t_mlx *mlx);
void			pixel_to_img(t_env *e, int col);

/*
** raytracer.c
*/
void			dispatcher_inters(t_obj *obj, double ray[3], double p[3]);

/*
** get_rays_and_intersections.c
*/
void			get_primary_ray(t_env *e);
void			get_inters_coord(double eye[3], double ray[3], \
									double dist, double inters[3]);
void			get_secondary_ray(t_env *e, t_light *spot);
void			get_reflexed_p_ray(t_env *e, double ray[3]);
void			get_reflexed_s_ray(t_env *e, double ray[3]);
/*
** equation_solver.c
*/
void			solve_equation(t_obj *obj, double var[3]);
/*
** trigonometry.c
*/
void			calc_trigonometry(double sincos[6], double angle[3], int flag);

/*
** vectors.c
*/
double			vect_dotprod(double a[3], double b[3]);
void			vect_dup(double v[3], double u[3]);
void			vect_norm(double v[3]);
void			vect_crossprod(double v[3], double u[3], double result[3]);
double			vect_cos(double norm[3], double ray[3]);
/*
** matrix.c
*/
void			rot_dir(double vect[3], double angle[3]);
void			rot_inv(double vect[3], double angle[3]);
void			trasl_dir(double vect[3], double v[3]);
void			trasl_inv(double vect[3], double v[3]);

/*
** color.c
*/
void			get_color(t_env *e);

/*
** reflexion.c
*/
void			reflexion(t_env *e, t_obj *obj);

/*
** transparence.c
*/
void			transparence(t_env *e, t_obj *obj);
/*
** shadows.c
*/
void			trace_shadows(t_env *e);

/*
** lightness.c
*/
void			lightness(t_env *e, t_obj *obj, t_light *spot);

/*
** chessboard_texture.c
*/
void			texture_dispatcher(t_env *e, t_obj *obj);

/*
** ------------------------- SPECIFIC OBJECTS FUNCTIONS -----------------------
*/

/*
** get_light.c
*/
void			get_light(t_env *e, char **data);

/*
** get_sphere.c
*/
void			get_sphere(t_env *e, char **data);

/*
** get_cylinder.c
*/
void			get_cyl(t_env *e, char **data);

/*
** get_cone.c
*/
void			get_cone(t_env *e, char **data);

/*
** get_plane.c
*/
void			get_plane(t_env *e, char **data);

/*
** get_torus.c
*/
void			get_torus(t_env *e, char **data);

/*
** get_disc.c
*/
void			get_disc(t_env *e, char **data);

/*
** get_paral.c
*/
void			get_paral(t_env *e, char **data);

/*
** get_triangle.c
*/
void			get_triangle(t_env *e, char **data);
#endif
