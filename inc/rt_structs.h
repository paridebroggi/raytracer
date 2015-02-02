#ifndef RT_STRUCTS_H
# define RT_STRUCTS_H
# include <rt.h>

typedef union u_color	t_color;
typedef struct s_pixel	t_pixel;
typedef struct s_obj	t_obj;
typedef struct s_mlx	t_mlx;
typedef struct s_env	t_env;
typedef struct s_ft		t_ft;
typedef struct s_error	t_error;
typedef struct s_intcol	t_intcol;
typedef struct s_light	t_light;

union				u_color
{
	int				num;
	unsigned char	comp[3];
};
struct				s_error

{
	int				type;
	const char		*msg;
};

struct				s_ft
{
	const char		*name;
	int				type;
	void			(*getdata)(t_env *, char **);
};

struct				s_pixel
{
	int				x;
	int				y;
};

struct				s_intcol
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
};

struct				s_light
{
	double			src[3];
	t_color			col;
	double			dist;
};

struct				s_obj
{
	double			c[3];
	double			cc[3];
	double			norm[3];
	double			inters[3];
	double			r;
	double			rr;
	double			h;
	double			a;
	double			rot[3];
	double			sincos[6];
	double			sincos_inv[6];
	t_color			col;
	double			dist;
	double			bright;
	double			reflex;
	double			trans;
	int				type;
	int				cut;
	int				chessboard;
	void			(*calc_inters)(t_env *, t_obj *, double [], double []);
	void			(*calc_norm)(t_obj *, double [], double []);
};

struct				s_mlx
{
	void			*id;
	void			*win;
	void			*img;
	char			*data;
	int				bpp;
	int				ls;
	int				edn;
	double			fov;
	double			w;
	double			h;
};

struct				s_env
{
	t_obj			obj[30];
	t_light			spot[10];
	double			p_ray[3];
	double			s_ray[3];
	double			r_ray[3];
	double			t_ray[3];
	double			inters[3];
	double			eye[3];
	double			eye_rot[3];
	double			sincos[6];
	double			sincos_inv[6];
	double			norm[3];
	size_t			nearest;
	t_intcol		intcol;
	t_mlx			mlx;
	t_pixel			pixel;
	t_color			pxcol;
	t_color			r_col;
	t_color			t_col;
	t_color			l_col;
	t_color			tmpcol;
	double			amb_light;
	double			air_refrac;
	size_t			n;
	size_t			l;
	int				check_win;
	int				check_eye;
};

#endif
