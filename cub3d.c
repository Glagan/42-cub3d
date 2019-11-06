/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 12:44:32 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/06 11:31:56 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3d.h"

int
	exit_hook(t_game *game)
{
	return (clear_game(game));
}

int
	key_press(int keycode, t_game *game)
{
	printf("{key: %d}\n", keycode);
	if (keycode == KEY_W)
		game->move.x = 1;
	else if (keycode == KEY_S)
		game->move.y = 1;
	else if (keycode == KEY_A)
		game->rotate.x = 1;
	else if (keycode == KEY_D)
		game->rotate.y = 1;
	return (0);
}

int
	key_release(int keycode, t_game *game)
{
	printf("{key: %d}\n", keycode);
	if (keycode == KEY_W)
		game->move.x = 0;
	else if (keycode == KEY_S)
		game->move.y = 0;
	else if (keycode == KEY_A)
		game->rotate.x = 0;
	else if (keycode == KEY_D)
		game->rotate.y = 0;
	else if (keycode == KEY_ESC)
		return (clear_game(game));
	return (0);
}

int
	main_loop(t_game *game)
{
	if (game->move.x)
		move_camera(game, 0);
	else if (game->move.y)
		move_camera(game, 1);
	if (game->rotate.x)
		rotate_camera(game, 0);
	else if (game->rotate.y)
		rotate_camera(game, 1);
	update_window(game);
	return (0);
}
