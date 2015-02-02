#include <rt.h>

void		get_shadows(t_env *e)
{
	size_t			n;
	unsigned char	*col;
	int				check;

	check = 0;
	col = (unsigned char *)&e->pxcol.num;
	n = 0;
	while (n < e->n)
	{
		if (n != e->nearest)
		{
			e->obj[n].calc_inters(e, &e->obj[n], e->s_ray, e->inters);
			if (e->obj[n].dist > 1e-6 && e->obj[n].dist < 1.0 && check == 0)
			{
				check = 1;
				col[B] = col[B] > 65 ? col[B] - 65 : 0;
				col[G] = col[G] > 65 ? col[G] - 65 : 0;
				col[R] = col[R] > 65 ? col[R] - 65 : 0;
			}
		}
		n++;
	}
}

void		trace_shadows(t_env *e)
{
	size_t	l;

	l = 0;
	while (l < e->l)
	{
		get_secondary_ray(e, &e->spot[l]);
		get_shadows(e);
		l++;
	}
}
