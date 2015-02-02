
NAME		= 	rt
CC			= 	gcc -g
CFLAGS		= 	-O3 -Werror -Wextra -Wall 
INCLUDES	= 	-I./inc/ 
LIBS		= 	-L./libs -lft -lcurses -lX11 -lXext -lmlx

FILES		= 	main.c \
				chessboard_texture.c \
				color.c \
				equation_solver.c \
				get_scene_data.c \
				get_rays_and_intersections.c \
				get_window_info.c \
				mlx.c \
				matrix.c \
				init_struct.c \
				lightness.c \
				loading_bar.c \
				get_light.c \
				get_cylinder.c \
				get_disc.c \
				get_cone.c \
				get_sphere.c \
				get_paral.c \
				get_plane.c \
				get_triangle.c \
				get_torus.c \
				transparence.c \
				trigonometry.c \
				raytracer.c \
				reflexion.c \
				shadows.c \
				vectors.c \
				usage_fail.c \

SRCS		= 	$(addprefix srcs/, $(FILES))
OBJS		= 	$(SRCS:.c=.o)

NOCOL=\x1b[0m
COL=\x1b[31;01m

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(LIBS)
	@echo "Built $(COL)$(NAME)$(NOCOL) completed."
%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@echo "Clean done."

fclean: clean
	@echo "Fclean done."
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re