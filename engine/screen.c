/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:38:10 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/06 20:28:40 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "engine.h"

static void
	draw_sky_floor(t_config *config, t_window *w, t_pos *pos)
{
	int		half;
	t_pos	l_pos;

	l_pos.x = pos->x;
	half = (int)pos->y / 2;
	l_pos.y = 0;
	draw_vertical_line_img(w, &l_pos, w->half.y - half, config->sky_color);
	l_pos.y = w->half.y + half;
	draw_vertical_line_img(w, &l_pos, w->half.y - half, config->floor_color);
}

static int
	wall_direction(t_game *game, t_raysult *ray)
{
	(void)game;

	if (ray->side)
	{
		if (ray->ray_dir.y < 0)
			return (DIR_NORTH);
		else
			return (DIR_SOUTH);
	}
	else if (ray->ray_dir.x < 0)
		return (DIR_WEST);
	return (DIR_EAST);
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

	direction = wall_direction(game, ray);
	tex = game->textures.t[direction];
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
		i = 0;
		while (i < ray->height)
		{
			pixel.y = start + i;
			if (pixel.y >= 0 && pixel.y < game->window.size.y)
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
	t_pos		line;
	t_raysult	ray;
	double		camera_x;

	w = &game->window;
	w->active_img = &w->screen;
	i = 0;
	while (i < w->size.x)
	{
		camera_x = ((2. * (double)i) / (double)game->window.size.x) - 1.;
		ray_cast(game, &ray, camera_x);
		ray.height = (int)fabs(w->size.y / ray.distance);
		if (ray.height > 0)
		{
			set_pos(&line, i, ray.height);
			if (ray.height < game->window.size.y)
				draw_sky_floor(&game->config, w, &line);
			draw_column(i, game, &ray);
		}
		else
		{
			set_pos(&line, i, 0);
			draw_sky_floor(&game->config, w, &line);
		}
		i++;
	}
}