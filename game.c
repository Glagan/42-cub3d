/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 12:51:35 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/09 17:06:28 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	exit_game(t_game *game, int code)
{
	clear_config(&game->config);
	clear_window(&game->window);
	clear_textures(game);
	clear_sprites(&game->sprites);
	exit(code);
	return (code);
}

void
	init_game(t_game *game, int save_opt)
{
	int	i;

	init_config(&game->config);
	set_pos(&game->move, 0, 0);
	set_pos(&game->x_move, 0, 0);
	set_pos(&game->rotate, 0, 0);
	game->options = 0x11111110;
	game->sprites = NULL;
	if (save_opt)
		game->options = game->options | FLAG_SAVE;
	i = 0;
	while (i < TEXTURES)
		game->tex[i++].tex = NULL;
}

int
	finish_init(t_game *game)
{
	find_start_pos(&game->config, &game->camera);
	find_start_angle(&game->config, &game->camera);
	if (!init_window(&game->window, &game->config))
	{
		return (exit_error(game,
			"Error:\nmlx failed to create window or image.\n"));
	}
	if (!load_textures(game))
		return (exit_error(game, "Error:\nfailed to load texture(s).\n"));
	if (!find_sprites(game))
		return (exit_error(game, "Error:\nfailed to malloc sprites.\n"));
	make_tables(game);
	return (1);
}

int
	screenshot(t_game *game)
{
	if (game->options & FLAG_UI)
		game->options = game->options ^ FLAG_UI;
	update_screen(game);
	update_window(game);
	mlx_do_sync(game->window.ptr);
	if (!save_png(game))
		exit_error(game, "Error:\nfailed to save screenshot.");
	return (exit_game(game, EXIT_SUCCESS));
}
