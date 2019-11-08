/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 23:18:31 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/07 23:18:31 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

t_sprite
	*add_sprite(t_game *game, t_sprite **sprites, t_raysult *ray)
{
	t_sprite 	*new;

	if (!(new = (t_sprite*)malloc(sizeof(*new))))
		return (NULL);
	new->side = ray->side;
	new->distance = ray_distance(game, ray);
	new->height = fabs(game->window.size.y / new->distance);
	copy_pos(&new->ray_pos, &ray->ray_pos);
	copy_pos(&new->map_pos, &ray->map_pos);
	new->next = *sprites;
	*sprites = new;
	return (new);
}

static void
	init_sprite_draw(t_tex *tex, t_sprite *sprite, t_pos *p_tex)
{
	double		sprite_x;

	if (sprite->side)
		sprite_x = sprite->ray_pos.x
			+ ((sprite->map_pos.y - sprite->ray_pos.y
				+ (1. - sprite->step.y) / 2.) / sprite->ray_dir.y)
			* sprite->ray_dir.x;
	else
		sprite_x = sprite->ray_pos.y
			+ ((sprite->map_pos.x - sprite->ray_pos.x
				+ (1. - sprite->step.x) / 2.) / sprite->ray_dir.x)
			* sprite->ray_dir.y;
	sprite_x -= floor(sprite_x);
	p_tex->x = (int)(sprite_x * tex->width);
	if (sprite->side == 0 && sprite->ray_dir.x > 0.)
		p_tex->x = tex->width - p_tex->x - 1.;
	else if (sprite->side == 1 && sprite->ray_dir.y < 0.)
		p_tex->x = tex->width - p_tex->x - 1.;
}

void
	draw_sprite_column(int column, t_game *game, t_sprite *sprite)
{
	int			i;
	int			start
	t_tex		*tex;
	t_pos		p_tex;
	t_pos		pixel;

	tex = &game->tex[TEX_SPRITE];
	set_pos(&pixel, column, max(0., game->window.half.y - (sprite->height / 2.)));
	init_sprite_draw(tex, sprite, &p_tex);
	start = max(0, game->window.half.y - (sprite->height / 2.));
	i = 0;
	while (i < sprite->height)
	{
		pixel.y = start + i;
		if (pixel.y > game->window.size.y)
			break ;
		if (pixel.y >= 0.)
		{
			p_tex.y = ((start + i) * 2 - game->window.size.y + sprite->height)
					* ((tex->height / 2.) / sprite->height);
			draw_pixel_img(&game->window, &pixel,
				tex ? get_tex_color(tex, &p_tex)
					: game->config.c[TEX_SPRITE]);
		}
		i++;
	}
}
