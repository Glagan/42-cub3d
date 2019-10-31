/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 12:44:32 by ncolomer          #+#    #+#             */
/*   Updated: 2019/10/31 15:16:24 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3d.h"

int
	key_event(int keycode, t_game *game)
{
	printf("{key press code:%d}\n", keycode);
	mlx_pixel_put(game->window->ptr, game->window->win, 0, 0, game->config->floor_color);
	return (1);
}

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
	/*int	x;
	int	y;
	int	color;

	color = 0xFFFFFF;
	y = 0;
	while (y < game->window->height)
	{
		x = 0;
		while (x < game->window->width)
		{
			mlx_pixel_put(game->window->ptr, game->window->win, x++, y, game->config->floor_color);
			color -= 1;
			if (color < 0)
				color = 0xFFFFFF;
		}
		y++;
	}*/
	return (0);
}
