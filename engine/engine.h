/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 11:55:59 by ncolomer          #+#    #+#             */
/*   Updated: 2019/10/31 22:26:58 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include "mlx/mlx.h"
# include "config/config.h"

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_MOUSE_PRESS	4
# define X_EVENT_MOUSE_RELEASE	5
# define X_EVENT_MOUSE_MOVE		6
# define X_EVENT_EXIT			17

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
	int		angle;
	t_pos	pos;
}				t_camera;

typedef	struct	s_game
{
	t_config	*config;
	t_window	*window;
	t_camera	*camera;
}				t_game;

t_camera		*new_camera(t_config *config);

t_window		*new_window(t_config *config);

int				draw_line(t_window *window, t_pos *p1, t_pos *p2, int color);

int				draw_rectangle(t_window *window, t_pos *p1, t_pos *wh, int color);

int				draw_string(t_window *window, t_pos *s_pos, char *str, int color);

int				clear_window(t_window *window);

void			update_window(t_game *game);

#endif
