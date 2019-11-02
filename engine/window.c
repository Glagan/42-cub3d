/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 12:53:02 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/02 13:09:29 by ncolomer         ###   ########.fr       */
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

int
	shade_color(int color, double divide)
{
	int	new;

	if (divide <= 1.)
		return (color);
	new = ((int)(((0xFF0000 & color) >> 16) / divide) << 16)
		+ ((int)(((0x00FF00 & color) >> 8) / divide) << 8)
		+ ((int)((0x0000FF & color) / divide));
	return (new);
}

/*static void
	draw_sky_floor(t_game *game)
{
	int		i;
	t_pos	p;
	t_pos	wh;
	int		shade_height;

	shade_height = game->window->height / 20.;
	set_pos(&wh, game->window->width, shade_height);
	p.x = 0;
	i = 0;
	while (i < 10)
	{
		p.y = i * shade_height;
		draw_rectangle(game->window, &p, &wh,
			shade_color(game->config->sky_color, 1. + (.5 * i)));
		p.y = game->window->height - ((i + 1) * shade_height);
		draw_rectangle(game->window, &p, &wh,
			shade_color(game->config->floor_color, 1. + (.5 * i)));
		i++;
	}
}*/

/**
 * TODO: Fix this shit :)
 **/
static void
	ray_cast(t_game *game, t_raysult *ray, t_pos *pos, double angle)
{
	int		hit;
	t_pos	distance;
	t_pos	direction;
	t_pos	ray_pos;
	t_pos	map_pos;

	(void)game;
	(void)ray;
	(void)pos;
	(void)angle;

	/**
	 * Horizontal
	 **/

	hit = 0;
	while (!hit)
	{
		if (angle < M_PI) // ray going up
		{
			set_pos(&ray_pos, 0, floor(pos->y - 1.));
			set_pos(&direction, 0, -1);
		}
		else
		{
			set_pos(&ray_pos, 0, floor(pos->y + 1.));
			set_pos(&direction, 0, 1);
		}
		direction.x = 1. / tan(M_PI);
		ray_pos.x = (pos->x + (pos->y - ray_pos.y)) / tan(angle);
		set_pos(&map_pos, ray_pos.x + direction.x, ray_pos.y + direction.y);
		if (MAP(map_pos, game->config) == '1')
			hit = 1;
	}
	distance.x = fabs(pos->x - ray_pos.x) / cos(M_PI);

	/**
	 * Vertical
	 **/

	hit = 0;
	while (!hit)
	{
		if (angle > M_PI_2 && angle < M_3_PI_2) // ray going left
		{
			set_pos(&ray_pos, floor(pos->x - 1.), 0);
			set_pos(&direction, -1, 0);
		}
		else
		{
			set_pos(&ray_pos, floor(pos->x + 1.), 0);
			set_pos(&direction, 1, 0);
		}
		direction.y = tan(M_PI);
		ray_pos.y = (pos->y + (pos->x - ray_pos.x)) / tan(angle);
		set_pos(&map_pos, ray_pos.x + direction.x, ray_pos.y + direction.y);
		if (MAP(map_pos, game->config) == '1')
			hit = 1;
	}
	distance.y = fabs(pos->x - ray_pos.x) / cos(M_PI);
	printf("{distance: %lfx %lfy}\n", distance.x, distance.y);
}

void
	update_window(t_game *game)
{
	int			i;
	t_raysult	ray;
	double		angle_step;
	double		projection_distance;
	double		projection_start;

	clear_window(game->window);
	//draw_sky_floor(game);
	projection_distance = (game->window->width / 2) / tan(M_PI_4);
	angle_step = M_PI_2 / game->window->width;
	projection_start = game->camera->angle - M_PI_4;
	i = 0;
	while (i < game->window->width)
	{
		ray_cast(game, &ray, &game->camera->pos, projection_start + (angle_step * i));
		i++;
	}
}
