/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:38:10 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/08 17:43:49 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void
	draw_sky_floor(t_game *game, int column, t_raysult *ray)
{
	t_pos	floor_wall;
	int		i;
	t_pos	pixel;
	double	weight;
	t_pos	p_tex;
	t_pos	c_floor;
	t_tex	*tex;

	if (ray->side == 0 && ray->ray_dir.x > 0)
		set_pos(&floor_wall, ray->map_pos.x, ray->map_pos.y + ray->wall_x);
	else if (ray->side == 0 && ray->ray_dir.x < 0)
		set_pos(&floor_wall, ray->map_pos.x + 1., ray->map_pos.y + ray->wall_x);
	else if (ray->side && ray->ray_dir.y > 0)
		set_pos(&floor_wall, ray->map_pos.x + ray->wall_x, ray->map_pos.y);
	else if (ray->side && ray->ray_dir.y < 0)
		set_pos(&floor_wall, ray->map_pos.x + ray->wall_x, ray->map_pos.y + 1.);
	pixel.x = column;
	tex = &game->tex[TEX_SKY];
	i = game->window.half.y + (ray->height / 2.);
	while (i < game->window.size.y)
	{
		weight = game->sf_dist[i] / ray->distance;
		set_pos(&c_floor, weight * floor_wall.x + (1. - weight) * game->camera.pos.x,
					weight * floor_wall.y + (1. - weight) * game->camera.pos.y);
		pixel.y = i;
		if (!game->tex[TEX_FLOOR].tex)
			draw_pixel_img(&game->window, &pixel,
				shade_color(game->config.c[TEX_FLOOR],
					(game->options & FLAG_SHADOWS) ? game->sf_dist[i] / 1.5 : 1));
		else
		{
			set_pos(&p_tex, (int)(c_floor.x * tex->width) % tex->width,
						(int)(c_floor.y * tex->height) % tex->height);
			draw_pixel_img(&game->window, &pixel,
				shade_color(get_tex_color(&game->tex[TEX_FLOOR], &p_tex),
					(game->options & FLAG_SHADOWS) ? game->sf_dist[i] / 1.5 : 1));
		}
		pixel.y = game->window.size.y - i++;
		if (!game->tex[TEX_SKY].tex)
			draw_pixel_img(&game->window, &pixel,
				shade_color(game->config.c[TEX_SKY],
					(game->options & FLAG_SHADOWS) ? game->sf_dist[i] / 1.5 : 1));
		else
		{
			set_pos(&p_tex, (int)(c_floor.x * tex->width) % tex->width,
						(int)(c_floor.y * tex->height) % tex->height);
			draw_pixel_img(&game->window, &pixel,
				shade_color(get_tex_color(&game->tex[TEX_SKY], &p_tex),
					(game->options & FLAG_SHADOWS) ? game->sf_dist[i] / 1.5 : 1));
		}
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
	if (!tex->tex)
		return (draw_vertical_line_img(&game->window, &pixel, ray->height,
			shade_color(game->config.c[ray->direction],
			(game->options & FLAG_SHADOWS) ? ray->distance / 1.5 : 1)));
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
				shade_color(get_tex_color(tex, &p_tex),
				(game->options & FLAG_SHADOWS) ? ray->distance / 1.5 : 1));
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
		game->depth[i] = ray.distance;
		ray.height = fabs(w->size.y / ray.distance);
		draw_column(i, game, &ray);
		if (ray.height < game->window.size.y)
			draw_sky_floor(game, i, &ray);
		i++;
	}
	if (game->sprites)
		draw_sprites(game);
	if (game->options & FLAG_CROSSHAIR)
		display_crosshair(game);
	return (1);
}
