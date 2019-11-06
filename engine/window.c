/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 12:53:02 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/06 13:37:46 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <time.h>
#include "engine.h"

void
    *destroy_window(t_window *win)
{
    if (win->image.img)
        mlx_destroy_image(win->ptr, win->image.img);
    if (win->ptr && win->win)
        mlx_destroy_window(win->ptr, win->win);
    free(win);
    return (NULL);
}

int
	clear_window(t_window *window)
{
	return (mlx_clear_window(window->ptr, window->win));
}

t_window
	*new_window(t_config *config)
{
	t_window	*window;

	if (!(window = (t_window*)malloc(sizeof(*window))))
		return (NULL);
	window->width = config->requested_width;
	window->height = config->requested_height;
    window->ptr = NULL;
    window->win = NULL;
	if (!(window->ptr = mlx_init())
		|| !(window->win =	mlx_new_window(
			window->ptr,
			window->width,
			window->height,
			"cub3d"))
		)
        return (destroy_window(window));
    set_pos(&window->size, window->width, window->height);
    set_pos(&window->half, window->width / 2, window->height / 2);
    init_image(window, &window->image);
    return (window);
}

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
	update_window(t_game *game)
{
	t_window	*w;
	int			i;
	int			height;
	t_pos		line;
	t_raysult	ray;
	double		camera_x;

	w = game->window;
	clear_window(w);
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
    mlx_put_image_to_window(w->ptr, w->win, w->image.img, 0, 0);
	//printf("{done}\n");
	debug_print_camera(game);
}
