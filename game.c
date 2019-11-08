/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 12:51:35 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/08 19:05:26 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	init_game(t_game *game, int save_opt)
{
	set_pos(&game->move, 0, 0);
	set_pos(&game->x_move, 0, 0);
	set_pos(&game->rotate, 0, 0);
	game->options = 0x11111110;
	if (save_opt)
		game->options = game->options | FLAG_SAVE;
}

int
	finish_init(t_game *game)
{
	init_camera(&game->config, &game->camera);
	if (!init_window(&game->window, &game->config))
		return (exit_error(game, "Error:\nmlx failed to create window.\n"));
	if (!load_textures(game))
		return (exit_error(game, "Error:\nfailed to load texture(s).\n"));
	if (!find_sprites(game))
		return (exit_error(game, "Error:\nfailed to malloc sprites.\n"));
	make_tables(game);
	return (EXIT_SUCCESS);
}

int
	clear_game(t_game *game)
{
	destroy_window(&game->window);
	// TODO: Free evertyhing
	exit(0);
	return (0);
}

int
	screenshot(t_game *game)
{
	if (game->options & FLAG_UI)
		game->options = game->options ^ FLAG_UI;
	if (!update_screen(game))
		return (clear_game(game));
	update_window(game);
	mlx_do_sync(game->window.ptr);
	return (save_png(game));
}
