/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 12:44:32 by ncolomer          #+#    #+#             */
/*   Updated: 2019/10/31 17:12:45 by ncolomer         ###   ########.fr       */
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
	key_event(int keycode, t_game *game)
{
	char	*str;
	t_pos	s_pos;

	printf("{key press code:%d}\n", keycode);
	pos(&s_pos, 5, 2);
	str = ft_itoa(keycode);
	clear_window(game->window);
	draw_string(game->window, &s_pos, str, 0xFFFFFF);
	free(str);
	return (0);
}

int
	mouse_event(int button, int x, int y, t_game *game)
{
	int		color;
	t_pos	r_pos;
	t_pos	dest;

	printf("{click button:%d x:%3d y:%3d}\n", button, x, y);
	pos(&r_pos, x, y);
	pos(&dest, game->window->width / 2, game->window->height / 2);
	if (button == LEFT_CLICK)
		color = 0xFFFF00;
	else if (button == RIGHT_CLICK)
		color = 0x00FFFF;
	else
		color = 0xFF00FF;
	clear_window(game->window);
	draw_line(game->window, &dest, &r_pos, 0xFFFFFF);
	return (0);
}

int
	main_loop(t_game *game)
{
	(void)game;
	//clear_window(game->window);
	return (0);
}
