#include <float.h>
#include <mlx.h>
#include <libft.h>
#include <rt.h>

void				cast_ray_through_all_objs(t_env *e)
{
	double			dist_min;
	size_t			n;

	n = 0;
	dist_min = FLT_MAX;
	get_primary_ray(e);
	while (n < e->n)
	{
		e->obj[n].calc_inters(e, &e->obj[n], e->p_ray, e->eye);
		if (e->obj[n].dist > 1e-6 && e->obj[n].dist < dist_min)
		{
			dist_min = e->obj[n].dist;
			e->nearest = n;
			e->pxcol = e->obj[n].col;
		}
		n++;
	}
	if (e->pxcol.num != 0)
		get_color(e);
}

void				raytracer(t_env *e)
{
	int			h;
	int			w;

	init_ncurses(&h, &w);
	e->pixel.y = 0.0f;
	while (e->pixel.y < (int)e->mlx.h)
	{
		e->pixel.x = 0.0f;
		while (e->pixel.x < (int)e->mlx.w)
		{
			e->pxcol.num = 0;
			cast_ray_through_all_objs(e);
			pixel_to_img(e, mlx_get_color_value(e->mlx.id, e->pxcol.num));
			e->pixel.x++;
		}
		e->pixel.y++;
		loading_percentage(e, h, w);
	}
}
