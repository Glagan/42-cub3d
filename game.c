/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 12:51:35 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/08 12:36:32 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	init_game(t_game *game)
{
	set_pos(&game->move, 0, 0);
	set_pos(&game->rotate, 0, 0);
}

int
	clear_game(t_game *game)
{
	destroy_window(&game->window);
	// TODO: Free evertyhing
	exit(0);
	return (0);
}
