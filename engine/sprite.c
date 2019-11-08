/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 23:18:31 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/08 14:23:16 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void
	draw_sprite(t_game *game, t_sprite *sprite, double inv_det)
{
	t_pos	pos;
	t_pos	transform;
	int		sprite_screen;
	t_pos	spr_s;
	int		i;
	int		j;
	t_pos	draw_x;
	t_pos	draw_y;
	t_pos	tex_pos;
	t_tex	*tex;
	int		d;
	int		color;
	t_pos	pixel;

	tex = &game->tex[TEX_SPRITE];
	set_pos(&pos, sprite->pos.x - game->camera.pos.x,
				sprite->pos.y - game->camera.pos.y);
	set_pos(&transform, inv_det * (game->camera.dir.y * pos.x - game->camera.dir.x * pos.y),
					inv_det * (-game->camera.plane.y * pos.x + game->camera.plane.x * pos.y));
	sprite_screen = (int)((game->window.size.x / 2.) * (1. + transform.x / transform.y));
	spr_s.x = fabs(game->window.size.y / transform.y);
	spr_s.y = fabs(game->window.size.y / transform.y);
	set_pos(&draw_x, (int)(max(0, -spr_s.x / 2. + sprite_screen)),
					(int)(max(0, spr_s.x / 2. + sprite_screen)));
	set_pos(&draw_y, (int)(max(0, -spr_s.y / 2. + game->window.size.y / 2.)),
					(int)(max(0, spr_s.y / 2. + game->window.size.y / 2.)));
	i = draw_x.x;
	//printf("{draw %lfx %lfy to %lfx %lfy}\n", draw_x.x, draw_x.y, draw_y.x, draw_y.y);
	while (i < game->window.size.x && i < draw_x.y)
	{
		pixel.x = i;
		tex_pos.x = (int)(256 * ((i - (-spr_s.x / 2. + sprite_screen))) * tex->width / spr_s.x) / 256;
		j = draw_y.x;
		if (transform.y > 0. && transform.y < game->depth[i])
		{
			while (j < game->window.size.y && j < draw_y.y)
			{
				pixel.y = j;
				d = (j * 256.) - (game->window.size.y * 128.) + (spr_s.y * 128.);
				tex_pos.y = ((d * tex->height) / spr_s.y) / 256.;
				color = get_tex_color(tex, &tex_pos);
				if (color != 0x0)
					draw_pixel_img(&game->window, &pixel, color);
				j++;
			}
		}
		i++;
	}
}

int
	draw_sprites(t_game *game)
{
	t_sprite	*sorted;
	double		inv_det;

	inv_det = 1. / ((game->camera.plane.x * game->camera.dir.y)
				- (game->camera.plane.y * game->camera.dir.x));
	sorted = sort_sprites(game, game->sprites);
	while (sorted)
	{
		draw_sprite(game, sorted, inv_det);
		sorted = sorted->sorted;
	}
	return (1);
}

int
	find_sprites(t_game *game)
{
	int		i;
	int		j;
	t_pos	pos;

	game->sprites = NULL;
	i = 0;
	while (i < game->config.rows)
	{
		pos.y = i;
		j = 0;
		while (j < game->config.columns)
		{
			pos.x = j;
			if (MAP(pos, game->config) == '2'
				&& !add_front_sprite(&game->sprites, 0., &pos))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
