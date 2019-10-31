/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 12:44:32 by ncolomer          #+#    #+#             */
/*   Updated: 2019/10/31 14:49:18 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3d.h"

int
	mouse_event(int button, int x, int y, t_game *game)
{
	printf("{click button:%d x:%d y:%d}\n", button, x, y);
	mlx_pixel_put(game->window->ptr, game->window->win, x, y, game->config->floor_color);
	return (1);
}

int
	main_loop(t_game *game)
{
	(void)game;
	return (0);
}
