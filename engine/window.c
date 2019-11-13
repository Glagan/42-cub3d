/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:59:23 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/13 15:41:38 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int
	clear_window(t_window *window)
{
	if (window->screen.img)
		mlx_destroy_image(window->ptr, window->screen.img);
	if (window->ptr && window->win)
		mlx_destroy_window(window->ptr, window->win);
	return (0);
}

int
	init_image(t_window *window, t_image *img)
{
	if (!(img->img =
		mlx_new_image(window->ptr, window->size.x, window->size.y)))
		return (0);
	img->ptr = mlx_get_data_addr(
		img->img, &img->bpp, &img->size_line, &img->endian);
	return (1);
}

int
	init_window(t_window *window, t_config *config)
{
	set_pos(&window->size, config->requested_width, config->requested_height);
	if (window->size.x > 1920)
		window->size.x = 1920;
	if (window->size.y > 1080)
		window->size.y = 1080;
	if (window->size.x < 848)
		window->size.x = 848;
	if (window->size.y < 480)
		window->size.y = 480;
	window->ptr = NULL;
	window->win = NULL;
	window->ratio = window->size.x / window->size.y;
	window->screen.img = NULL;
	if (window->ratio < BEST_RATIO)
		config->fov = config->fov / ((BEST_RATIO / config->fov) / 2.5);
	else if (window->ratio > BEST_RATIO)
		config->fov = config->fov * ((config->fov / BEST_RATIO) * 2.5);
	if (!(window->ptr = mlx_init())
		|| !(window->win = mlx_new_window(
			window->ptr, window->size.x, window->size.y, "cub3d")))
		return (0);
	set_pos(&window->half, window->size.x / 2, window->size.y / 2);
	if (!init_image(window, &window->screen))
		return (0);
	return (1);
}

void
	update_window(t_game *game)
{
	t_window	*w;

	w = &game->window;
	mlx_put_image_to_window(w->ptr, w->win, w->screen.img, 0, 0);
	if (game->options & FLAG_UI)
		write_ui_text(game);
}
