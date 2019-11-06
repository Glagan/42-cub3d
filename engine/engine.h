/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 11:55:59 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/06 20:28:27 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include <math.h>
# include "mlx/mlx.h"
# include "config/config.h"

# define DIR_NORTH	0
# define DIR_SOUTH	1
# define DIR_WEST	2
# define DIR_EAST	3
# define DIR_SPRITE	4

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_MOUSE_PRESS	4
# define X_EVENT_MOUSE_RELEASE	5
# define X_EVENT_MOUSE_MOVE		6
# define X_EVENT_EXIT			17

# define M_2_M_PI	(M_PI * 2.)
# define M_PI_3		(M_PI / 3.)
# define M_PI_6		(M_PI / 6.)
# define M_PI_12	(M_PI / 12.)
# define M_3_PI_2	((3. * M_PI) / 2.)
# define M_3_PI_4	((3. * M_PI) / 4.)
# define M_5_PI_4	((5. * M_PI) / 4.)
# define M_7_PI_4	((7. * M_PI) / 4.)

# define WALL_HEIGHT	64
# define SPEED			.2

typedef struct	s_raysult
{
	double	distance;
	int		direction;
	int		side;
	int		height;
	t_pos	ray_pos;
	t_pos	ray_dir;
	t_pos	map_pos;
	t_pos	side_dist;
	t_pos	delta_dist;
	t_pos	step;
}				t_raysult;

typedef struct	s_image
{
	void	*img;
	void	*ptr;
	int		bpp;
	int		size_line;
	int		endian;
}				t_image;

typedef struct	s_tex
{
	char	*path;
	void	*tex;
	void	*ptr;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}				t_tex;

typedef struct	s_textures
{
	t_tex	north;
	t_tex	south;
	t_tex	west;
	t_tex	east;
	t_tex	sprite;
	t_tex	*t[5];
}				t_textures;

typedef	struct	s_window
{
	void		*ptr;
	void		*win;
    t_image		screen;
    t_image		ui;
	t_image		*active_img;
	t_pos		size;
	t_pos		half;
	int			show_ui;
}				t_window;

typedef struct	s_camera
{
	t_pos	pos;
	t_pos	dir;
	t_pos	plane;
}				t_camera;

typedef	struct	s_game
{
	t_config	config;
	t_window	window;
	t_camera	camera;
	t_textures	textures;
	t_pos		move;
	t_pos		rotate;
}				t_game;

void			init_camera(t_config *config, t_camera *camera);

int				move_camera(t_game *game, int direction);

int				rotate_camera(t_game *game, int direction);

int				init_window(t_window *window, t_config *config);

int				clear_window(t_window *window);

int				destroy_window(t_window *win);

void			update_screen(t_game *game);

void			clear_ui(t_window *window);

void			update_ui(t_game *game);

void			write_ui_text(t_game *game);

void			update_window(t_game *game);

int				load_textures(t_game *game);

int				draw_string(t_window *window, t_pos *s_pos, char *str,
					int color);

double			ray_cast(t_game *game, t_raysult *ray, double camera_x);

void			init_image(t_window *window, t_image *img);

void			destroy_image(t_window *window, t_image *img);

void			draw_pixel_img(t_window *w, t_pos *pos, int color);

int				draw_vertical_line_img(t_window *window, t_pos *start,
					int length, int color);

int				draw_rectangle_img(t_window *window, t_pos *p1,
					t_pos *p2, int color);

int				shade_color(int color, double divide);

int				get_tex_color(t_tex *tex, t_pos *pos);

//

void debug_print_camera(t_game *game);

#endif
