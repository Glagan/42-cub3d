/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 23:18:31 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/09 17:34:33 by ncolomer         ###   ########.fr       */
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

static void
	set_tex_pos(t_game *game, t_sprite_draw *spr, t_tex *tex,
		t_pos *tex_pos)
{
	tex_pos->x = (int)(256
		* (((int)(spr->draw_x.x) - (-spr->spr_s.x / 2. + spr->sprite_screen)))
			* tex->width / spr->spr_s.x) / 256;
	spr->fact = ((int)(spr->draw_y.x) * 256.) - (game->window.size.y * 128.)
		+ (spr->spr_s.y * 128.);
	tex_pos->y = ((spr->fact * tex->height) / spr->spr_s.y) / 256.;
}

static void
	draw_sprite(t_game *game, t_sprite *sprite, t_sprite_draw *spr,
		t_tex *tex)
{
	t_pos	pixel;
	t_pos	tex_pos;
	int		color;

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
				set_pos(&pixel, spr->draw_x.x, spr->draw_y.x);
				set_tex_pos(game, spr, tex, &tex_pos);
				color = shade_color(get_tex_color(tex, &tex_pos),
					(game->options & FLAG_SHADOWS) ? sprite->distance / 3 : 1);
				if (color != 0x0)
					draw_pixel(&game->window, &pixel, color);
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

int
	find_sprites(t_game *game)
{
	int		i;
	int		j;
	t_pos	pos;
	char	c;
	t_tex	*tex;

	game->sprites = NULL;
	i = 0;
	while (i < game->config.rows)
	{
		j = 0;
		while (j < game->config.columns)
		{
			set_pos(&pos, j + .5, i + .5);
			c = MAP(pos, game->config);
			tex = (c == '2') ? &game->tex[TEX_SPRITE]
							: &game->tex[TEX_SPRITE_UP];
			if ((c == '2' || c == '3') && tex->tex
				&& !add_front_sprite(&game->sprites, 0., &pos, tex))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
