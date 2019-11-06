/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 12:44:32 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/06 18:47:38 by ncolomer         ###   ########.fr       */
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
	if (keycode == KEY_W)
		game->move.x = 1;
	else if (keycode == KEY_S)
		game->move.y = 1;
	if (keycode == KEY_A)
		game->rotate.x = 1;
	else if (keycode == KEY_D)
		game->rotate.y = 1;
	/*else if (keycode == KEY_Q)
		game->rotate.x = 1;
	else if (keycode == KEY_E)
		game->rotate.y = 1;*/
	return (0);
}

int
	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->move.x = 0;
	else if (keycode == KEY_S)
		game->move.y = 0;
	if (keycode == KEY_A)
		game->rotate.x = 0;
	else if (keycode == KEY_D)
		game->rotate.y = 0;
	/*else if (keycode == KEY_Q)
		game->rotate.x = 0;
	else if (keycode == KEY_E)
		game->rotate.y = 0;*/
	else if (keycode == KEY_ESC)
		return (clear_game(game));
	else if (keycode == KEY_I)
	{
		game->window.show_ui = !game->window.show_ui;
		if (game->window.show_ui)
			printf("UI: ON\n");
		else
			printf("UI: OFF\n");
	}
	return (0);
}

int
	main_loop(t_game *game)
{
	static int	update = 1;
	static int	last_ui = 1;

	if (game->move.x)
		update = move_camera(game, 0);
	else if (game->move.y)
		update = move_camera(game, 1);
	if (game->rotate.x)
		update = rotate_camera(game, 0);
	else if (game->rotate.y)
		update = rotate_camera(game, 1);
	if (last_ui != game->window.show_ui)
	{
		update = 1;
		last_ui = game->window.show_ui;
	}
	if (update)
	{
		debug_print_camera(game);
		update_screen(game);
		update_ui(game);
		update_window(game);
	}
	update = 0;
	return (0);
}
