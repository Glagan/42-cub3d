/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_png.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 18:10:05 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/08 19:10:49 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	save_png(t_game *game)
{
	t_libattopng	*png;
	int				x;
	int				y;
	int				tmp;

	png = libattopng_new(game->window.size.x, game->window.size.y, PNG_RGBA);
	y = 0;
	while (y < game->window.size.y)
	{
		x = 0;
		while (x < game->window.size.x)
		{
			tmp = *(int*)(game->window.active_img->ptr
					+ (4 * (int)game->window.size.x * y)
					+ (4 * x));
			libattopng_set_pixel(png, x, y,
				RGB((tmp & 0x00FF0000) >> 16,
					(tmp & 0x0000FF00) >> 8,
					tmp & 0x000000FF));
			x++;
		}
		y++;
	}
	libattopng_save(png, "screenshot.png");
	libattopng_destroy(png);
	clear_game(game);
	return (EXIT_SUCCESS);
}
