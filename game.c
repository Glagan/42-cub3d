/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 12:51:35 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/01 12:36:49 by ncolomer         ###   ########.fr       */
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
	return (game);
}

int
	clear_game(t_game *game)
{
	mlx_destroy_window(game->window->ptr, game->window->win);
	exit(0);
	return (0);
}
