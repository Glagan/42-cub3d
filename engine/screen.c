/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:38:10 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/07 17:01:13 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "engine.h"

static void
	draw_sky_floor(t_game *game, int column, t_raysult *ray)
{
	t_pos	sky_tex;
	int		i;
	int		j;
	t_pos	pixel;

	if (game->tex[TEX_SKY].tex)
		sky_tex.x = column % game->tex[TEX_SKY].width;
	j = 0;
	pixel.x = column;
	i = game->window.size.y;
	while (i > game->window.half.y + (ray->height / 2.))
	{
		if (game->tex[TEX_SKY].tex)
			sky_tex.y = j % game->tex[TEX_SKY].height;
		pixel.y = j++;
		draw_pixel_img(&game->window, &pixel,
			(game->tex[TEX_SKY].tex)
			? get_tex_color(&game->tex[TEX_SKY], &sky_tex)
			: game->config.c[TEX_SKY]);
		pixel.y = i--;
		draw_pixel_img(&game->window, &pixel, game->config.c[TEX_FLOOR]);
	}
}

void
	draw_column(int column, t_game *game, t_raysult *ray)
{
	int		i;
	int		start;
	t_pos	p_tex;
	t_tex	*tex;
	t_pos	pixel;
	int		limit;

	tex = &game->tex[ray->direction];
	set_pos(&pixel, column, max(0., game->window.half.y - (ray->height / 2.)));
	if (tex)
	{
		if (ray->side)
			ray->wall_x = ray->ray_pos.x
					+ ((ray->map_pos.y - ray->ray_pos.y + (1. - ray->step.y) / 2.)
					/ ray->ray_dir.y) * ray->ray_dir.x;
		else
			ray->wall_x = ray->ray_pos.y
					+ ((ray->map_pos.x - ray->ray_pos.x + (1. - ray->step.x) / 2.)
					/ ray->ray_dir.x) * ray->ray_dir.y;
		ray->wall_x -= floor(ray->wall_x);
		p_tex.x = (int)(ray->wall_x * tex->width);
		if (ray->side == 0 && ray->ray_dir.x > 0.)
			p_tex.x = tex->width - p_tex.x - 1.;
		if (ray->side == 1 && ray->ray_dir.y < 0.)
			p_tex.x = tex->width - p_tex.x - 1.;
		start = max(0, game->window.half.y - (ray->height / 2.));
		limit = (ray->height > game->window.size.y)
				? game->window.size.y : ray->height;
		i = 0;
		while (i < ray->height)
		{
			pixel.y = start + i;
			if (pixel.y > game->window.size.y)
				break ;
			if (pixel.y >= 0.)
			{
				p_tex.y = ((start + i) * 2 - game->window.size.y + ray->height)
						* ((tex->height / 2.) / ray->height);
				draw_pixel_img(&game->window, &pixel,
					tex ? get_tex_color(tex, &p_tex) : game->config.c[ray->direction]);
			}
			i++;
		}
	}
	else
		draw_vertical_line_img(&game->window, &pixel,
			ray->height, game->config.c[ray->direction]);
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
		ray.height = fabs(w->size.y / ray.distance);
		if (ray.height > 0)
		{
			if (ray.height < game->window.size.y)
				draw_sky_floor(game, i, &ray);
			draw_column(i, game, &ray);
		}
		else
			draw_sky_floor(game, i, &ray);
		i++;
	}
}