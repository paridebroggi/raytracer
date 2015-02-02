#include <stdlib.h>
#include <mlx.h>
#include <libft.h>
#include <rt.h>

void				init_mlx(t_mlx *mlx)
{
	mlx->id = mlx_init();
	if (mlx->id == NULL)
		fail(MLX);
	mlx->img = mlx_new_image(mlx->id, (int)mlx->w, (int)mlx->h);
	if (mlx->img == NULL)
		fail(MLX);
	if ((mlx->data = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->ls,
		&mlx->edn)) == NULL)
	{
		fail(MLX);
	}
}

void				show_final_window(t_mlx *mlx)
{
	mlx->win = mlx_new_window(mlx->id, (int)mlx->w, (int)mlx->h, "RT");
	if (mlx->win == NULL)
		fail(MLX);
}

int					expose_handler(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->id, mlx->win, mlx->img, 0, 0);
	return (0);
}

int					key_hook_handler(int keycode, t_mlx *mlx)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(mlx->id, mlx->win);
		end_curses();
		exit(0);
	}
	return (0);
}

void				pixel_to_img(t_env *e, int col)
{
	unsigned int	pos;

	pos = e->pixel.y * e->mlx.ls + e->pixel.x * e->mlx.bpp / 8;
	memcpy(e->mlx.data + pos, &col, 4);
}
