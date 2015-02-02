#include <rt.h>
#include <mlx.h>

int			main(int argc, char **argv)
{
	t_env	e;

	if (argc != 2)
	{
		usage();
		return (0);
	}
	get_scene(&e, argv[1]);
	init_mlx(&e.mlx);
	raytracer(&e);
	show_final_window(&e.mlx);
	mlx_expose_hook(e.mlx.win, expose_handler, &e.mlx);
	mlx_key_hook(e.mlx.win, key_hook_handler, &e.mlx);
	mlx_loop(e.mlx.id);
	return (0);
}
