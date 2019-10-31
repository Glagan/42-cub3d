/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 12:53:02 by ncolomer          #+#    #+#             */
/*   Updated: 2019/10/31 22:42:26 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "engine.h"

t_window
	*new_window(t_config *config)
{
	t_window	*window;

	if (!(window = (t_window*)malloc(sizeof(*window))))
		return (NULL);
	window->width = config->requested_width;
	window->height = config->requested_height;
	if (!(window->ptr = mlx_init())
		|| !(window->win =	mlx_new_window(
			window->ptr,
			window->width,
			window->height,
			"cub3d"))
		)
	{
		free(window);
		return (NULL);
	}
	window->origin.x = 0;
	window->origin.y = 0;
	window->size.x = window->width;
	window->size.y = window->height;
	return (window);
}

int
	clear_window(t_window *window)
{
	return (mlx_clear_window(window->ptr, window->win));
}

void
	update_window(t_game *game)
{
	int	i;
	int	j;

	clear_window(game->window);
	i = 0;
	while (i < game->config->rows)
	{
		j = 0;
		while (j < game->config->columns)
		{
			if (i == game->camera->pos.y && j == game->camera->pos.x)
				printf("  ");
			else
				printf("%c ", game->config->map[(i * game->config->columns) + j]);
			j++;
		}
		if (i == game->config->rows - 1)
			printf("\n");
		else
			printf("\n");
		i++;
	}
	printf("#CAMERA" \
		"\nx:\t%d" \
		"\ny:\t%d" \
		"\nangle:\t%d (degrees)\n",
		game->camera->pos.x, game->camera->pos.y, game->camera->angle);
}
