/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 12:44:32 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/10 15:08:26 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	exit_hook(t_game *game)
{
	return (exit_game(game, EXIT_SUCCESS));
}

int
	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == KEY_FORWARD)
		game->move.x = 1;
	else if (keycode == KEY_S || keycode == KEY_BACKWARD)
		game->move.y = 1;
	if (keycode == KEY_A)
		game->x_move.x = 1;
	else if (keycode == KEY_D)
		game->x_move.y = 1;
	if (keycode == KEY_Q || keycode == KEY_LEFT)
		game->rotate.x = 1;
	else if (keycode == KEY_E || keycode == KEY_RIGHT)
		game->rotate.y = 1;
	return (0);
}

int
	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == KEY_FORWARD)
		game->move.x = 0;
	else if (keycode == KEY_S || keycode == KEY_BACKWARD)
		game->move.y = 0;
	else if (keycode == KEY_A)
		game->x_move.x = 0;
	else if (keycode == KEY_D)
		game->x_move.y = 0;
	else if (keycode == KEY_Q || keycode == KEY_LEFT)
		game->rotate.x = 0;
	else if (keycode == KEY_E || keycode == KEY_RIGHT)
		game->rotate.y = 0;
	else if (keycode == KEY_ESC)
		return (exit_game(game, EXIT_SUCCESS));
	else if (keycode == KEY_I)
		game->options = game->options ^ FLAG_UI;
	else if (keycode == KEY_L)
		game->options = game->options ^ FLAG_SHADOWS;
	else if (keycode == KEY_O)
		game->options = game->options ^ FLAG_CROSSHAIR;
	return (0);
}

int
	main_loop(t_game *game)
{
	static int	update = 1;
	static int	last_opt = 0x00000111;

	if (game->move.x || game->move.y)
		update = move_camera(game, (game->move.x) ? 0 : 1);
	if (game->x_move.x || game->x_move.y)
		update = move_perp_camera(game, (game->x_move.x) ? 0 : 1);
	if (game->rotate.x || game->rotate.y)
		update = rotate_camera(game, (game->rotate.x) ? 0 : 1);
	if (last_opt != game->options)
	{
		update = 1;
		last_opt = game->options;
	}
	if (update)
	{
		if (game->to_collect > 0)
			check_quest(game);
		MAP(game->camera.pos, game->config) = 'A';
		update_screen(game);
		update_window(game);
	}
	update = 0;
	return (0);
}
