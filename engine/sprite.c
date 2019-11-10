/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 23:18:31 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/10 14:36:05 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void
	init_draw_sprite(t_game *game, t_sprite *sprite, double inv_det,
		t_sprite_draw *spr)
{
	set_pos(&spr->pos, sprite->pos.x - game->camera.pos.x,
				sprite->pos.y - game->camera.pos.y);
	set_pos(&spr->transform,
		inv_det * (game->camera.dir.y * spr->pos.x
					- game->camera.dir.x * spr->pos.y),
		inv_det * (-game->camera.plane.y * spr->pos.x
					+ game->camera.plane.x * spr->pos.y));
	spr->sprite_screen = (int)((game->window.size.x / 2.)
						* (1. + spr->transform.x / spr->transform.y));
	spr->spr_s.x = fabs(game->window.size.y / spr->transform.y);
	spr->spr_s.y = fabs(game->window.size.y / spr->transform.y);
	set_pos(&spr->draw_x,
		(int)(MAX(0, -spr->spr_s.x / 2. + spr->sprite_screen)),
		(int)(MAX(0, spr->spr_s.x / 2. + spr->sprite_screen)));
	set_pos(&spr->draw_y,
		(int)(MAX(0, -spr->spr_s.y / 2. + game->window.size.y / 2.)),
		(int)(MAX(0, spr->spr_s.y / 2. + game->window.size.y / 2.)));
	spr->draw_y_org = spr->draw_y.x;
}

static int
	set_tex_pos(t_game *game, t_sprite_draw *spr, t_tex *tex,
		t_pos *tex_pos)
{
	tex_pos->x = (int)(256
		* (((int)(spr->draw_x.x) - (-spr->spr_s.x / 2. + spr->sprite_screen)))
			* tex->width / spr->spr_s.x) / 256;
	if (tex_pos->x < tex->start.x || tex_pos->x > tex->end.x)
		return (0);
	spr->fact = ((int)(spr->draw_y.x) * 256.) - (game->window.size.y * 128.)
		+ (spr->spr_s.y * 128.);
	tex_pos->y = ((spr->fact * tex->height) / spr->spr_s.y) / 256.;
	return (tex_pos->y > tex->start.y && tex_pos->y < tex->end.y);
}

static void
	draw_sprite_pixel(t_game *game, t_sprite *sprite, t_sprite_draw *spr,
		t_tex *tex)
{
	t_pos	pixel;
	t_pos	tex_pos;
	int		color;

	set_pos(&pixel, spr->draw_x.x, spr->draw_y.x);
	if (set_tex_pos(game, spr, tex, &tex_pos))
	{
		color = shade_color(get_tex_color(tex, &tex_pos),
			(game->options & FLAG_SHADOWS) ? sprite->distance / 3 : 1);
		if (color != 0x0)
			draw_pixel(&game->window, &pixel, color);
	}
}

static void
	draw_sprite(t_game *game, t_sprite *sprite, t_sprite_draw *spr,
		t_tex *tex)
{
	while (spr->draw_x.x < game->window.size.x
		&& spr->draw_x.x < spr->draw_x.y)
	{
		if (spr->transform.y > 0.
			&& spr->transform.y < game->depth[(int)spr->draw_x.x])
		{
			spr->draw_y.x = spr->draw_y_org;
			while (spr->draw_y.x < game->window.size.y
				&& spr->draw_y.x < spr->draw_y.y)
			{
				draw_sprite_pixel(game, sprite, spr, tex);
				spr->draw_y.x++;
			}
		}
		spr->draw_x.x++;
	}
}

void
	draw_sprites(t_game *game)
{
	t_sprite		*sorted;
	double			inv_det;
	t_sprite_draw	spr;

	inv_det = 1. / ((game->camera.plane.x * game->camera.dir.y)
				- (game->camera.plane.y * game->camera.dir.x));
	sorted = sort_sprites(game, game->sprites);
	while (sorted)
	{
		if (sorted->distance > .1)
		{
			init_draw_sprite(game, sorted, inv_det, &spr);
			draw_sprite(game, sorted, &spr, sorted->tex);
		}
		sorted = sorted->sorted;
	}
}
