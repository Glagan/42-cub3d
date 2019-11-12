/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sky_floor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 14:40:26 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/12 17:10:47 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void
	init_draw_sky_floor(t_raysult *ray)
{
	if (ray->side == 0 && ray->ray_dir.x > 0)
		set_pos(&ray->floor_wall,
			ray->map_pos.x, ray->map_pos.y + ray->wall_x);
	else if (ray->side == 0 && ray->ray_dir.x < 0)
		set_pos(&ray->floor_wall,
			ray->map_pos.x + 1., ray->map_pos.y + ray->wall_x);
	else if (ray->side && ray->ray_dir.y > 0)
		set_pos(&ray->floor_wall,
			ray->map_pos.x + ray->wall_x, ray->map_pos.y);
	else if (ray->side && ray->ray_dir.y < 0)
		set_pos(&ray->floor_wall,
			ray->map_pos.x + ray->wall_x, ray->map_pos.y + 1.);
}

static void
	draw_sky_pixel(t_game *game, t_raysult *ray, t_pos *pixel, t_pos *p_tex)
{
	t_tex	*tex;

	tex = &game->tex[TEX_SKY];
	if (!game->tex[TEX_SKY].tex)
	{
		draw_pixel(&game->window, pixel,
			distance_shade(game->options, game->config.c[TEX_SKY],
			game->sf_dist[ray->row]));
	}
	else
	{
		set_pos(p_tex, (int)(ray->c_floor.x * tex->width) % tex->width,
					(int)(ray->c_floor.y * tex->height) % tex->height);
		draw_pixel(&game->window, pixel,
			distance_shade(game->options, get_tex_color(tex, p_tex),
			game->sf_dist[ray->row]));
	}
}

static void
	draw_floor_pixel(t_game *game, t_raysult *ray, t_pos *pixel, t_pos *p_tex)
{
	t_tex	*tex;

	tex = &game->tex[TEX_FLOOR];
	if (!tex->tex)
	{
		draw_pixel(&game->window, pixel,
			distance_shade(game->options, game->config.c[TEX_FLOOR],
			game->sf_dist[ray->row]));
	}
	else
	{
		set_pos(p_tex, (int)(ray->c_floor.x * tex->width) % tex->width,
					(int)(ray->c_floor.y * tex->height) % tex->height);
		draw_pixel(&game->window, pixel,
			distance_shade(game->options, get_tex_color(tex, p_tex),
			game->sf_dist[ray->row]));
	}
}

void
	draw_sky_floor(t_game *game, t_raysult *ray)
{
	int		i;
	t_pos	pixel;
	double	weight;
	t_pos	p_tex;

	init_draw_sky_floor(ray);
	pixel.x = ray->column;
	i = game->window.half.y + (ray->height / 2.);
	while (i < game->window.size.y)
	{
		ray->row = (int)i;
		weight = game->sf_dist[i] / ray->distance;
		set_pos(&ray->c_floor,
			weight * ray->floor_wall.x + (1. - weight) * game->camera.pos.x,
			weight * ray->floor_wall.y + (1. - weight) * game->camera.pos.y);
		pixel.y = i;
		draw_floor_pixel(game, ray, &pixel, &p_tex);
		pixel.y = game->window.size.y - i++;
		draw_sky_pixel(game, ray, &pixel, &p_tex);
	}
}
