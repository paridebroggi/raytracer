#include <unistd.h>
#include <fcntl.h>
#include <libft.h>
#include <rt.h>

t_ft	g_ft[] =
{
	{ ".window", 0, get_window},
	{ ".eye", 0, get_eye},
	{ ".light", LIGHT, get_light},
	{ ".sphere", SPHERE, get_sphere},
	{ ".plane", PLANE, get_plane},
	{ ".cylinder", CYL, get_cyl},
	{ ".cone", CONE, get_cone},
	{ ".torus", TORUS, get_torus},
	{ ".disc", DISC, get_disc},
	{ ".paral", PARAL, get_paral},
	{ ".triangle", TRIANGLE, get_triangle},
	{ NULL, 0, 0}
};

static int		open_scene(char *path)
{
	int			fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		fail(OPEN);
	return (fd);
}

static void		parser(t_env *e, char *line)
{
	char		**tab;
	int			i;

	tab = ft_strsplit(line, ' ');
	i = 0;
	while (g_ft[i].name)
	{
		if (strcmp(tab[0], g_ft[i].name) == 0)
		{
			init_obj(e);
			g_ft[i].getdata(e, tab);
			ft_tabdel(&tab);
			return ;
		}
		i++;
	}
	ft_tabdel(&tab);
	fail(OBJNOTF);
}

static void		check_essentials(t_env *e)
{
	if (e->check_win == 0)
		fail(CHECK_WINDOW);
	if (e->n == 0)
		fail(CHECK_OBJECTS);
	if (e->l == 0)
		fail(CHECK_LIGHTS);
	if (e->check_eye == 0)
		fail(CHECK_EYE);
}

void			get_scene(t_env *e, char *arg)
{
	char		*line;
	int			fd;

	fd = open_scene(arg);
	e->n = 0;
	e->l = 0;
	e->check_win = 0;
	e->check_eye = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (*line)
			parser(e, line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	close (fd);
	check_essentials(e);
}
