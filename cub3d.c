/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 12:44:32 by ncolomer          #+#    #+#             */
/*   Updated: 2019/10/31 22:43:44 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3d.h"

int
	exit_hook(t_game *game)
{
	mlx_destroy_window(game->window->ptr, game->window->win);
	exit(0);
	return (0);
}

int
	move_camera(t_game *game, t_pos *pos, int direction)
{
	t_camera	*camera;

	camera = game->camera;
	if (camera->angle >= 225 && camera->angle <= 315)
		pos->y += (-direction);
	else if (camera->angle >= 45 && camera->angle <= 135)
		pos->y += (direction);
	if (camera->angle >= 315 || camera->angle <= 45)
		pos->x += (direction);
	else if (camera->angle >= 135 && camera->angle <= 225)
		pos->x += (-direction);
	printf("{trying to move to x%dy%d}\n", pos->x, pos->y);
	if (pos->x < game->config->columns && pos->y < game->config->rows
		&& game->config->map[(pos->y * game->config->columns) + pos->x] == '0')
	{
		printf("{moved to x%dy%d}\n", pos->x, pos->y);
		copy_pos(&camera->pos, pos);
		return (1);
	}
	return (0);
}

int
	key_event(int keycode, t_game *game)
{
	t_pos		new_pos;
	t_camera	*camera;
	int			update;

	printf("{key press code:%d}\n", keycode);
	camera = game->camera;
	update = 1;
	copy_pos(&new_pos, &camera->pos);
	if (keycode == KEY_W)
		update = move_camera(game, &new_pos, 1);
	else if (keycode == KEY_A)
		camera->angle = (camera->angle == 0) ? 315 : camera->angle - 45;
	else if (keycode == KEY_D)
		camera->angle = (camera->angle + 45) % 360;
	else if (keycode == KEY_S)
		update = move_camera(game, &new_pos, -1);
	if (update)
		update_window(game);
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
	(void)game;
	//clear_window(game->window);
	return (0);
}
