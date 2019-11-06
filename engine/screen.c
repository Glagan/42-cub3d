/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:38:10 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/06 14:43:21 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void
	update_screen(t_game *game)
{
	t_window	*w;
	int			i;
	int			height;
	t_pos		line;
	t_raysult	ray;
	double		camera_x;

	w = game->window;
	w->active_img = &w->screen;
	i = 0;
	while (i < w->width)
	{
		camera_x = ((2. * (double)i) / (double)game->window->width) - 1.;
		ray_cast(game, &ray, camera_x);
		height = fabs((double)w->height / ray.distance);
		if (height > 0)
		{
			set_pos(&line, i, height);
			draw_sky_floor(game->config, w, &line);
			set_pos(&line, i, w->half.y - (height / 2));
			draw_vertical_line_img(w, &line, height,
				shade_color((ray.side) ? 0xFFFFFF : 0xEEEEEE, ray.distance / 3.));
		}
		else
		{
			set_pos(&line, i, 0);
			draw_sky_floor(game->config, w, &line);
		}
		i++;
	}
}