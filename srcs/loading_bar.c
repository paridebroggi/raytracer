#include <ncurses.h>
#include <rt.h>

void				init_ncurses(int *h, int *w)
{
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	getmaxyx(stdscr, *h, *w);
	*w = *w / 2;
	*h = *h / 2 - 1;
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	mvprintw(*h, *w - 26, "|");
	mvprintw(*h, *w + 26, "|");
	attron(COLOR_PAIR(1));
	*w -= 25;
}

void				end_curses(void)
{
	keypad(stdscr, TRUE);
	curs_set(1);
	endwin();
}

void				loading_percentage(t_env *e, int h, int w)
{
	int		i;

	i = ((e->pixel.y * e->pixel.x + 1) * 100) / (e->mlx.w * e->mlx.h);
	if (i % 2 == 0)
	{
		mvprintw(h, w + (i / 2), "|");
		refresh();
	}
}
