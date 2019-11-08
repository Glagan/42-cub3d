/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_png.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 18:10:05 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/08 18:20:20 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
void
	prepare_loop_png(t_game *game, t_libattopng **ppng, int *py)
{
	draw(p);
	mlx_put_image_to_window(p->mlx.mlx_ptr,
		p->mlx.win, p->mlx.img.img_ptr, 0, 0);
}

int
	save_png(t_game *game)
{
	t_libattopng	*png;
	int				x;
	int				y;
	int				tmp;

	prepare_loop_png(game, &png, &y);
	png = libattopng_new(game->window.size.x, game->window.size.y, PNG_RGBA);
	y = 0;
	while (y < game->window.size.y)
	{
		x = 0;
		while (x < game->window.size.x)
		{
			tmp = game->mlx.img.data[p->win_width * y + x];

			pix.r = (tmp & 0x00FF0000) >> 16;
			pix.g = (tmp & 0x0000FF00) >> 8;
			pix.b = (tmp & 0x000000FF);
			libattopng_set_pixel(png, x, y, RGB(pix.r, pix.g, pix.b));
			x++;
		}
		y++;
	}
	libattopng_save(png, "screenshot.png");
	libattopng_destroy(png);
	clear_game(game);
	return (EXIT_SUCCESS);
}
*/