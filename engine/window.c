/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 12:53:02 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/01 19:51:08 by ncolomer         ###   ########.fr       */
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
	(void)game;
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

void
	update_window(t_game *game)
{
	int			i;
	double 		cameraX;
	t_pos		ray_dir;
	t_pos		map;
	t_pos		side_dist;
	t_pos		delta_dist;
	double 		perp_wall_dist;
	t_pos		step;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	t_pos		line_start;
	t_pos		line_end;

	clear_window(game->window);
	//draw_sky_floor(game);
	i = 0;
	while (i < game->window->width)
	{
		cameraX = 2 * i / (double)game->window->width - 1;
		set_pos(&ray_dir,
			game->camera->dir_vec.x + game->camera->plane.x * cameraX,
			game->camera->dir_vec.y + game->camera->plane.y * cameraX);
		set_pos(&map, (int)game->camera->pos.x, (int)game->camera->pos.y);
		set_pos(&delta_dist, fabs(1. / ray_dir.x), fabs(1. / ray_dir.y));
		hit = 0;
		if (ray_dir.x < 0)
		{
			step.x = -1;
			side_dist.x = (game->camera->pos.x - map.x) * delta_dist.x;
		}
		else
		{
			step.x = 1;
			side_dist.x = (map.x + 1.0 - game->camera->pos.x) * delta_dist.x;
		}
		if (ray_dir.y < 0)
		{
			step.y = -1;
			side_dist.y = (game->camera->pos.y - map.y) * delta_dist.y;
		}
		else
		{
			step.y = 1;
			side_dist.y = (map.y + 1.0 - game->camera->pos.y) * delta_dist.y;
		}
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (side_dist.x < side_dist.y)
			{
				side_dist.x += delta_dist.x;
				map.x += step.x;
				side = 0;
			}
			else
			{
				side_dist.y += delta_dist.y;
				map.y += step.y;
				side = 1;
			}
			if (MAP(map, game->config) >= '1')
				hit = 1;
		}
		if (side == 0)
			perp_wall_dist = (map.x - game->camera->pos.x + (1 - step.x) / 2.) / ray_dir.x;
		else
			perp_wall_dist = (map.y - game->camera->pos.y + (1 - step.y) / 2.) / ray_dir.y;
		line_height = (int)(game->window->height / perp_wall_dist);
		printf("{line_height:%d}\n", line_height);
		draw_start = -line_height / 2. + game->window->height / 2.;
		if(draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2. + game->window->height / 2.;
		if(draw_end >= game->window->height)
			draw_end = game->window->height - 1;
		set_pos(&line_start, i, draw_start);
		set_pos(&line_end, i, draw_start + line_height);
		draw_line(game->window, &line_start, &line_end, 0xFFFFFF);
		i++;
	}
}
