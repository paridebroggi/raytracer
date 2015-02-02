#include <math.h>
#include <stdlib.h>
#include <rt.h>

static void		pied_de_poule_texture(t_env *e, t_obj *obj)
{
	int			x;
	int			y;
	double		copy_inters[3];

	vect_dup(copy_inters, e->inters);
	rot_inv(copy_inters, obj->sincos_inv);
	y = (int)copy_inters[Y] - 100000;
	x = (int)copy_inters[X] - 100000;
	if (abs(x % 6) > 3)
	{
		if (abs(y % 6) > 3)
			e->tmpcol.num = 2;
		else
			e->tmpcol = obj->col;
	}
	else
	{
		if (abs(y % 6) <= 3)
			e->tmpcol.num = 2;
		else
			e->tmpcol = obj->col;
	}
}

static void		chessboard_texture(t_env *e, t_obj *obj)
{
	int			x;
	int			y;
	double		copy_inters[3];

	vect_dup(copy_inters, e->inters);
	rot_inv(copy_inters, obj->sincos_inv);
	x = CHESSB_SIZE / 2 * (copy_inters[X] < 0 ? -1 : 1);
	y = CHESSB_SIZE / 2 * (copy_inters[Y] < 0 ? -1 : 1);
	if (fmod(copy_inters[X], CHESSB_SIZE) > x)
	{
		if (fmod(copy_inters[Y], CHESSB_SIZE) > y)
			e->tmpcol.num = 2;
		else
			e->tmpcol = obj->col;
	}
	else
	{
		if (fmod(copy_inters[Y], CHESSB_SIZE) < y)
			e->tmpcol.num = 2;
		else
			e->tmpcol = obj->col;
	}
}

void			texture_dispatcher(t_env *e, t_obj *obj)
{
	if (obj->chessboard != 1)
	{
		pied_de_poule_texture(e, obj);
		return ;
	}
	chessboard_texture(e, obj);
}
