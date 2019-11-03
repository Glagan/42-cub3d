/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 12:53:02 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/03 17:32:04 by ncolomer         ###   ########.fr       */
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
	set_pos(&window->origin, 0, 0);
	set_pos(&window->size, window->width, window->height);
	set_pos(&window->half, window->width / 2, window->height / 2);
	window->projection_distance = window->half.x / tan(config->fov / 2.);
	window->angle_step = (double)config->fov / (double)window->width;
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

void
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
}

static void
	ray_cast(t_game *game, t_raysult *ray, t_pos *pos, double angle)
{
	int		hit;
	t_pos	direction;
	t_pos	ray_pos;
	t_pos	map_pos;
	t_pos	distance;

	/**
	 * Horizontal
	 **/

	set_pos(&distance, 9999, 9999);
	if (angle != M_PI && angle != 0)
	{
		if (angle < M_PI) // ray going up
		{
			ray_pos.y = floor(pos->y - 1.);
			direction.y = -1;
		}
		else
		{
			ray_pos.y = floor(pos->y + 1.);
			direction.y = 1;
		}
		ray_pos.x = pos->x + (pos->y - ray_pos.y) / tan(angle);
		direction.x = 1. / tan(angle);
		hit = 0;
		copy_pos(&map_pos, &ray_pos);
		while (!hit)
		{
			if (map_pos.x < 0 || map_pos.x > game->config->columns
				|| map_pos.y < 0 || map_pos.y > game->config->columns)
				hit = 1;
			if (MAP(map_pos, game->config) == '1' && (hit =1))
				distance.x = fabs(map_pos.x - pos->x) / cos(angle);
			set_pos(&map_pos, map_pos.x + direction.x, map_pos.y + direction.y);
		}
	}

	/**
	 * Vertical
	 **/

	if (angle != M_PI_2 && angle != M_3_PI_2)
	{
		if (angle > M_PI_2 || angle < M_3_PI_2) // ray going left
		{
			ray_pos.x = floor(pos->x - 1.);
			direction.x = -1;
		}
		else
		{
			ray_pos.x = floor(pos->x + 1.);
			direction.x = 1;
		}
		ray_pos.y = pos->y + (pos->x - ray_pos.x) * tan(angle);
		direction.y = tan(angle);
		hit = 0;
		copy_pos(&map_pos, &ray_pos);
		while (!hit)
		{
			if (map_pos.x < 0 || map_pos.x > game->config->columns
				|| map_pos.y < 0 || map_pos.y > game->config->columns)
				hit = 1;
			if (MAP(map_pos, game->config) == '1' && (hit = 1))
				distance.y = fabs(map_pos.x - pos->x) / cos(angle);
			set_pos(&map_pos, map_pos.x + direction.x, map_pos.y + direction.y);
		}
	}
	ray->distance = (distance.x < distance.y) ? distance.x : distance.y;
}

/**
 * TODO: make it work...
 **/
void
	update_window(t_game *game)
{
	t_window	*w;
	int			i;
	t_raysult	ray;
	double		half_fov;
	int			height;
	t_pos		start;

	w = game->window;
	clear_window(w);
	//draw_sky_floor(game);
	half_fov = game->config->fov / 2;
	printf("{camera_angle %lf half %lf angle_step %lf}\n", game->camera->angle, half_fov, w->angle_step);
	i = 0;
	while (i < w->width)
	{
		ray_cast(game, &ray, &game->camera->pos, game->camera->angle + (i * w->angle_step) - half_fov);
		ray.distance = fabs(ray.distance * cos(i * w->angle_step));
		height = 1. / ray.distance * (double)w->projection_distance;
		//printf("{height: %d}\n", height);
		set_pos(&start, i, (w->height / 2) - (height / 2));
		draw_vertical_line(w, &start, height, 0xFFFFFF);
		i++;
	}
	printf("{done}\n");
}
