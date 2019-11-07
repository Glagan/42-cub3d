/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:38:10 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/07 12:24:31 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "engine.h"

static void
	draw_sky_floor(t_game *game, t_raysult *ray)
{
	(void) game;
	(void) ray;
}

/**
 * TODO: Slow when really near walls
 **/
void
	draw_column(int column, t_game *game, t_raysult *ray)
{
	int		i;
	int		start;
	t_pos	wall;
	t_pos	p_tex;
	t_tex	*tex;
	t_pos	pixel;
	int		direction;
	int		limit;

	direction = wall_direction(ray);
	tex = &game->tex[direction];
	set_pos(&pixel, column, game->window.half.y - (ray->height / 2.));
	if (tex)
	{
		if (ray->side)
			wall.x = ray->ray_pos.x
					+ ((ray->map_pos.y - ray->ray_pos.y + (1 - ray->step.y) / 2)
					/ ray->ray_dir.y) * ray->ray_dir.x;
		else
			wall.x = ray->ray_pos.y
					+ ((ray->map_pos.x - ray->ray_pos.x + (1 - ray->step.x) / 2)
					/ ray->ray_dir.x) * ray->ray_dir.y;
		wall.x -= floor(wall.x);
		p_tex.x = (int)(wall.x * tex->width);
		if (ray->side == 0 && ray->ray_dir.x > 0)
			p_tex.x = tex->width - p_tex.x - 1.;
		if (ray->side == 1 && ray->ray_dir.y < 0)
			p_tex.x = tex->width - p_tex.x - 1.;
		start = game->window.half.y - (ray->height / 2.);
		limit = (ray->height > game->window.size.y)
				? game->window.size.y : ray->height;
		i = 0;
		while (i < ray->height)
		{
			pixel.y = start + i;
			if (pixel.y > game->window.size.y)
				break ;
			if (pixel.y >= 0)
			{
				p_tex.y = ((start + i) * 2 - game->window.size.y + ray->height)
						* ((tex->height / 2.) / ray->height);
				draw_pixel_img(&game->window, &pixel,
					tex ? get_tex_color(tex, &p_tex) : game->config.c[direction]);
			}
			i++;
		}
	}
	else
		draw_vertical_line_img(&game->window, &pixel,
			ray->height, game->config.c[direction]);
}

void
	update_screen(t_game *game)
{
	t_window	*w;
	int			i;
	t_raysult	ray;

	w = &game->window;
	w->active_img = &w->screen;
	i = 0;
	while (i < w->size.x)
	{
		ray_cast(game, &ray, game->camera_x[i]);
		ray.height = (int)fabs(w->size.y / ray.distance);
		if (ray.height > 0)
		{
			if (ray.height < game->window.size.y)
				draw_sky_floor(game, &ray);
			draw_column(i, game, &ray);
		}
		else
			draw_sky_floor(game, &ray);
		i++;
	}
}