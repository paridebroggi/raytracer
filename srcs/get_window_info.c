#include <math.h>
#include <libft.h>
#include <rt.h>

void			get_window(t_env *e, char **data)
{
	double		angle;

	if (ft_tablen(data) != 5)
		fail(PARAM_WINDOW);
	e->mlx.w = (double)atoi(data[1] + 2);
	e->mlx.h = (double)atoi(data[2] + 2);
	angle = (double)atoi(data[3] + 4) * (M_PI / 180);
	e->mlx.fov = tan(angle * 0.5);
	e->amb_light = (double)atoi(data[4] + 10) / 10.0;
	e->check_win = 1;
}

void			get_eye(t_env *e, char **data)
{
	if (ft_tablen(data) != 7)
		fail(PARAM_EYE);
	e->eye[X] = (double)atoi(data[1] + 2);
	e->eye[Y] = (double)atoi(data[2] + 2);
	e->eye[Z] = (double)atoi(data[3] + 2);
	e->eye_rot[X] = (double)atoi(data[4] + 6) * (M_PI / 180);
	e->eye_rot[Y] = (double)atoi(data[5] + 6) * (M_PI / 180);
	e->eye_rot[Z] = (double)atoi(data[6] + 6) * (M_PI / 180);
	calc_trigonometry(e->sincos_inv, e->eye_rot, INV);
	calc_trigonometry(e->sincos, e->eye_rot, DIR);
	e->check_eye = 1;
}
