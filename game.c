/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 12:51:35 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/06 11:28:39 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game
	*new_game(void)
{
	t_game	*game;

	if (!(game = (t_game*)malloc(sizeof(*game))))
		return (NULL);
	game->window = NULL;
	game->config = NULL;
	game->camera = NULL;
	set_pos(&game->move, 0, 0);
	set_pos(&game->rotate, 0, 0);
	return (game);
}

int
	clear_game(t_game *game)
{
	destroy_window(game->window);
	// TODO: Free evertyhing
	exit(0);
	return (0);
}
