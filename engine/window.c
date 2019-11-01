/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 12:53:02 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/01 16:10:23 by ncolomer         ###   ########.fr       */
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

static void
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
	ray_cast(t_raysult *ray, t_pos *pos, double angle)
{
	int		hit;
	t_pos	step;
	double	sin_v;
    double	cos_v;

	(void)ray;
	(void)pos;
	(void)angle;

	copy_pos(&step, pos);
	hit = 0;
	while (!hit)
	{
		cos_v = cos(angle);
		sin_v = sin(angle);
		printf("{cosinus:%lf, sinus:%lf}\n", cos_v, sin_v);
		hit = 1;
	}
}

void
	update_window(t_game *game)
{
	int			i;
	t_raysult	ray;
	double		angle_step;

	clear_window(game->window);
	draw_sky_floor(game);
	i = 0;
	while (i < game->window->width)
	{
		// focal_length = 0.8 ?
		angle_step = atan2(((double)i / game->window->width) - .5, 0.8);
		/*ray.distance = 0;
		ray.side = 0;
		ray.wall_pos.x = 0;
		ray.wall_pos.y = 0;*/
		ray_cast(&ray, &game->camera->pos, game->camera->angle + angle_step);
		i++;
	}
}
