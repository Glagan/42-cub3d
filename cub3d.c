/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 12:44:32 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/03 18:03:50 by ncolomer         ###   ########.fr       */
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
	key_event(int keycode, t_game *game)
{
	t_camera	*camera;
	int			update;

	printf("{key press code:%d}\n", keycode);
	if (keycode == KEY_ESC)
		return (clear_game(game));
	camera = game->camera;
	update = 1;
	if (keycode == KEY_W)
		update = move_camera(game, camera->angle);
	else if (keycode == KEY_S)
		update = move_camera(game, -camera->angle);
	else if (keycode == KEY_A)
		camera->angle = fmod(camera->angle + M_PI_6, M_2_M_PI);
	else if (keycode == KEY_D)
	{
		camera->angle -= M_PI_6;
		if (camera->angle < 0.)
			camera->angle = M_2_M_PI + camera->angle;
	}
	if (update)
		update_window(game);
	debug_print_camera(game);
	return (0);
}

/*int
	mouse_event(int button, int x, int y, t_game *game)
{
	int		color;
	t_pos	pos;
	t_pos	dest;

	printf("{click button:%d x:%3d y:%3d}\n", button, x, y);
	set_pos(&pos, x, y);
	set_pos(&dest, game->window->width / 2, game->window->height / 2);
	if (button == LEFT_CLICK)
		color = 0xFFFF00;
	else if (button == RIGHT_CLICK)
		color = 0x00FFFF;
	else
		color = 0xFF00FF;
	clear_window(game->window);
	draw_line(game->window, &dest, &pos, 0xFFFFFF);
	return (0);
}*/

int
	main_loop(t_game *game)
{
	static int	updated = 0;

	if (!updated)
		update_window(game);
	updated = 1;
	return (0);
}
