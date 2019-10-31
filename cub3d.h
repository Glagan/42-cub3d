/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 12:44:11 by ncolomer          #+#    #+#             */
/*   Updated: 2019/10/31 17:09:02 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "engine/engine.h"
# include "config/config.h"
# include "utils/utils.h"

# define LEFT_CLICK 	1
# define RIGHT_CLICK 	2
# define MIDDLE_CLICK	3
# define SCROLL_UP		4
# define SCROLL_DOWN	5

# define W	13
# define A	0
# define S	1
# define D	2

# define LEFT_ARROW		123
# define RIGHT_ARROW	124
# define DOWN_ARROW		125
# define UP_ARROW		126

# define ESC	53
# define TAB	48

typedef	struct	s_game
{
	t_config	*config;
	t_window	*window;
	t_camera	*camera;
}				t_game;

t_game			*new_game(void);

int				key_event(int keycode, t_game *game);

int				mouse_event(int button, int x, int y, t_game *game);

int				exit_hook(t_game *game);

int				main_loop(t_game *game);

#endif
