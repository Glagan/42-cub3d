/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:38:10 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/09 14:58:46 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void
	update_screen(t_game *game)
{
	t_window	*w;
	int			i;
	t_raysult	ray;
	t_pos		start;

	w = &game->window;
	set_pos(&start, 0, 0);
	draw_rectangle(w, &start, &w->size, 0x0);
	i = 0;
	while (i < w->size.x)
	{
		ray_cast(game, &ray, i);
		game->depth[i] = ray.distance;
		ray.height = fabs(w->size.y / ray.distance);
		draw_wall(game, &ray);
		if (ray.height < game->window.size.y)
			draw_sky_floor(game, &ray);
		i++;
	}
	if (game->sprites)
		draw_sprites(game);
	if (game->options & FLAG_CROSSHAIR)
		display_crosshair(game);
	if (game->options & FLAG_UI)
		update_ui(game);
}
