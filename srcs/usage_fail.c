#include <stdio.h>
#include <stdlib.h>
#include <libft.h>
#include <rt.h>

t_error	g_err[] =
{
	{ OPEN, ": open failed" },
	{ MLX, ": mlx init failed" },
	{ OBJNOTF, ": object not found" },
	{ PARAM_SPHERE, ": sphere parameters didn't match" },
	{ PARAM_CYL, ": cylinder parameters didn't match" },
	{ PARAM_CONE, ": cone parameters didn't match" },
	{ PARAM_PLANE, ": plan parameters didn't match" },
	{ PARAM_TORUS, ": torus parameters didn't match" },
	{ PARAM_LIGHT, ": light parameters didn't match" },
	{ PARAM_WINDOW, ": window parameters didn't match" },
	{ PARAM_EYE, ": eye parameters didn't match" },
	{ CHECK_WINDOW, ": windows parameters missing" },
	{ CHECK_OBJECTS, ": no object in the scene" },
	{ CHECK_LIGHTS, ": no light in the scene" },
	{ CHECK_EYE, ": eye parameters missing" },
	{ PARAM_DISC, ": disc parameters missing" },
	{ PARAM_PARAL, ": paral parameters missing" },
	{ PARAM_TRIANGLE, ": triangle parameters missing" },
	{ 0, NULL },
};

void		fail(int err)
{
	ft_putstr("./rt: error");
	ft_putendl(g_err[err].msg);
	exit(-1);
}

void		usage(void)
{
	ft_putendl("usage: ./rt <scene>");
}
