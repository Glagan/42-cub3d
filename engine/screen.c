/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:38:10 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/08 13:24:54 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			shade_color((game->tex[TEX_SKY].tex)
			? get_tex_color(&game->tex[TEX_SKY], &sky_tex)
			: game->config.c[TEX_SKY], 0));
		pixel.y = i--;
		draw_pixel_img(&game->window, &pixel,
			shade_color(game->config.c[TEX_FLOOR], 1.5));
	}
}

static void
	init_draw_wall(t_tex *tex, t_raysult *ray, t_pos *p_tex)
{
	if (ray->side)
		ray->wall_x = ray->ray_pos.x
			+ ((ray->map_pos.y - ray->ray_pos.y
				+ (1. - ray->step.y) / 2.) / ray->ray_dir.y)
			* ray->ray_dir.x;
	else
		ray->wall_x = ray->ray_pos.y
			+ ((ray->map_pos.x - ray->ray_pos.x
				+ (1. - ray->step.x) / 2.) / ray->ray_dir.x)
			* ray->ray_dir.y;
	ray->wall_x -= floor(ray->wall_x);
	p_tex->x = (int)(ray->wall_x * tex->width);
	if (ray->side == 0 && ray->ray_dir.x > 0.)
		p_tex->x = tex->width - p_tex->x - 1.;
	else if (ray->side == 1 && ray->ray_dir.y < 0.)
		p_tex->x = tex->width - p_tex->x - 1.;
}

static int
	draw_column(int column, t_game *game, t_raysult *ray)
{
	int		i;
	int		start;
	t_pos	p_tex;
	t_tex	*tex;
	t_pos	pixel;

	tex = &game->tex[ray->direction];
	set_pos(&pixel, column, max(0, game->window.half.y - (ray->height / 2.)));
	if (!tex)
		return (draw_vertical_line_img(&game->window, &pixel, ray->height, shade_color(game->config.c[ray->direction], ray->distance / 1.5)));
	init_draw_wall(tex, ray, &p_tex);
	start = max(0, game->window.half.y - (ray->height / 2.));
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
				shade_color(tex ? get_tex_color(tex, &p_tex)
					: game->config.c[ray->direction], ray->distance / 1.5));
		}
		i++;
	}
	return (1);
}

int
	update_screen(t_game *game)
{
	t_window	*w;
	int			i;
	t_raysult	ray;
	t_pos		start;


	w = &game->window;
	w->active_img = &w->screen;
	set_pos(&start, 0, 0);
	draw_rectangle_img(w, &start, &w->size, 0x0);
	i = 0;
	while (i < w->size.x)
	{
		if (!ray_cast(game, &ray, game->camera_x[i]))
			return (0);
		ray.height = fabs(w->size.y / ray.distance);
		if (ray.height > 0)
		{
			if (ray.height < game->window.size.y)
				draw_sky_floor(game, i, &ray);
			draw_column(i, game, &ray);
		}
		else
			draw_sky_floor(game, i, &ray);
		if (game->sprites)
			draw_sprites(game);
		i++;
	}
	return (1);
}
