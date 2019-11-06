/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 12:44:32 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/06 12:19:45 by ncolomer         ###   ########.fr       */
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
	//printf("{key: %d}\n", keycode);
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
	//printf("{key: %d}\n", keycode);
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
	static int	update = 1;

	if (game->move.x)
		update = move_camera(game, 0);
	else if (game->move.y)
		update = move_camera(game, 1);
	if (game->rotate.x)
		update = rotate_camera(game, 0);
	else if (game->rotate.y)
		update = rotate_camera(game, 1);
	if (update)
		update_window(game);
	update = 0;
	return (0);
}
