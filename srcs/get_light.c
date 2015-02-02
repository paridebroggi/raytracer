#include <libft.h>
#include <rt.h>

void			get_light(t_env *e, char **data)
{
	if (ft_tablen(data) != 7)
		fail(PARAM_LIGHT);
	e->spot[e->l].src[X] = (double)atoi(data[1] + 2);
	e->spot[e->l].src[Y] = (double)atoi(data[2] + 2);
	e->spot[e->l].src[Z] = (double)atoi(data[3] + 2);
	e->spot[e->l].col.comp[B] = atoi(data[4] + 6);
	e->spot[e->l].col.comp[G] = atoi(data[5] + 6);
	e->spot[e->l].col.comp[R] = atoi(data[6] + 6);
	e->l++;
}
