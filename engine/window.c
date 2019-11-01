/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 12:53:02 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/01 14:04:52 by ncolomer         ###   ########.fr       */
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

static void
	ray_cast(t_raysult *ray, t_pos *pos, double angle)
{
	(void)ray;
	(void)pos;
	(void)angle;
}

void
	update_window(t_game *game)
{
	int			i;
	t_raysult	ray;
	double		angle_step;

	clear_window(game->window);
	angle_step = game->window->width / 0.8; // focal_length = 0.8 ?
	i = 0;
	while (i < game->window->width)
	{
		ray_cast(&ray, &game->camera->pos, game->camera->angle + (angle_step * i));
		i++;
	}
}
