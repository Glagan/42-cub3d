/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 12:44:11 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/06 11:21:01 by ncolomer         ###   ########.fr       */
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

# define KEY_W	13
# define KEY_A	0
# define KEY_S	1
# define KEY_D	2

# define KEY_LEFT_ARROW		123
# define KEY_RIGHT_ARROW	124
# define KEY_DOWN_ARROW		125
# define KEY_UP_ARROW		126

# define KEY_ESC	53
# define KEY_TAB	48

t_game			*new_game(void);

int				clear_game(t_game *game);

int				key_press(int keycode, t_game *game);

int				key_release(int keycode, t_game *game);

int				exit_hook(t_game *game);

int				main_loop(t_game *game);

#endif
