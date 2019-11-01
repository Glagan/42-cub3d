/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 11:55:59 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/01 14:21:07 by ncolomer         ###   ########.fr       */
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
# define M_PI_6		(M_PI / 6.)
# define M_PI_12	(M_PI / 12.)
# define M_3_PI_2	((3. * M_PI) / 2.)
# define M_3_PI_4	((3. * M_PI) / 4.)
# define M_5_PI_4	((5. * M_PI) / 4.)
# define M_7_PI_4	((7. * M_PI) / 4.)

typedef struct	s_raysult
{
	t_pos		wall_pos;
	double		distance;
	int			side;
}				t_raysult;

typedef	struct	s_window
{
	void		*ptr;
	void		*win;
	int			width;
	int			height;
	t_pos		origin;
	t_pos		size;
}				t_window;

typedef struct	s_camera
{
	double	angle;
	t_pos	pos;
}				t_camera;

typedef	struct	s_game
{
	t_config	*config;
	t_window	*window;
	t_camera	*camera;
}				t_game;

t_camera		*new_camera(t_config *config);

int				move_camera(t_game *game, double angle);

t_window		*new_window(t_config *config);

int				draw_line(t_window *window, t_pos *p1, t_pos *p2, int color);

int				draw_rectangle(t_window *window, t_pos *p1, t_pos *wh, int color);

int				draw_string(t_window *window, t_pos *s_pos, char *str, int color);

int				clear_window(t_window *window);

void			update_window(t_game *game);

//

void			debug_print_camera(t_game *game);

#endif
