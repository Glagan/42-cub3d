/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 11:55:59 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/06 12:34:17 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include <math.h>
# include "mlx/mlx.h"
# include "config/config.h"

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
	int		side;
	t_pos	ray_pos;
	t_pos	ray_dir;
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

typedef	struct	s_window
{
	void		*ptr;
	void		*win;
    t_image		image;
	int			width;
	int			height;
	t_pos		size;
	t_pos		half;
}				t_window;

typedef struct	s_camera
{
	t_pos	pos;
	t_pos	dir;
	t_pos	plane;
}				t_camera;

typedef	struct	s_game
{
	t_config	*config;
	t_window	*window;
	t_camera	*camera;
	t_pos		move;
	t_pos		rotate;
}				t_game;

t_camera		*new_camera(t_config *config);

int				move_camera(t_game *game, int direction);

int				rotate_camera(t_game *game, int direction);

t_window		*new_window(t_config *config);

int				clear_window(t_window *window);

void            *destroy_window(t_window *win);

void			update_window(t_game *game);

int				draw_line(t_window *window, t_pos *p1, t_pos *p2, int color);

int				draw_vertical_line(t_window *window, t_pos *start,
					int length, int color);

int				draw_rectangle(t_window *window, t_pos *p1, t_pos *wh,
					int color);

int				draw_string(t_window *window, t_pos *s_pos, char *str,
					int color);

double			ray_cast(t_game *game, t_raysult *ray, double camera_x);

void			init_image(t_window *window, t_image *img);

void			destroy_image(t_window *window, t_image *img);

int				draw_vertical_line_img(t_window *window, t_pos *start,
					int length, int color);

int				shade_color(int color, double divide);

//

void debug_print_camera(t_game *game);

#endif
