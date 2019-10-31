/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 12:45:06 by ncolomer          #+#    #+#             */
/*   Updated: 2019/10/31 14:56:48 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "cub3d.h"

void
	printf_infos(t_game *game)
{
	int			i;
	int			j;
	t_config	*config;
	t_camera	*camera;
	t_window	*window;

	config = game->config;
	printf("#CONFIG" \
		"\nwidth\t\t%d" \
		"\nheight\t\t%d" \
		"\nno_texture\t\"%s\"" \
		"\nso_texture\t\"%s\"" \
		"\nwe_texture\t\"%s\"" \
		"\nea_texture\t\"%s\"" \
		"\nsprite_texture\t\"%s\"" \
		"\nsky_color\t#%x" \
		"\nfloor_color\t#%x" \
		"\nmap\t\t%dx%d\n",
		config->requested_width, config->requested_height,
		config->north_texture_path, config->south_texture_path,
		config->west_texture_path, config->east_texture_path,
		config->sprite_texture_path, config->sky_color, config->floor_color,
		config->columns, config->rows
	);
	i = 0;
	while (i < config->rows)
	{
		j = 0;
		while (j < config->columns)
			printf("%c ", config->map[(i * config->columns) + j++]);
		if (i == config->rows - 1)
			printf("\n");
		else
			printf("\n");
		i++;
	}

	camera = game->camera;
	printf("#CAMERA" \
		"\nx:\t%d" \
		"\ny:\t%d" \
		"\nangle:\t%d (degrees)\n",
		camera->x, camera->y, camera->angle);

	window = game->window;
	printf("#WINDOW" \
		"\nwidth:\t%d" \
		"\nheight:\t%d" \
		"\nptr:\t%p" \
		"\nwindow:\t%p\n",
		window->width, window->height, window->ptr, window->win);
}

int
	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2) // TODO: look for -save
		return (EXIT_FAILURE); // TODO: print error
	if (!(game = new_game()))
		return (EXIT_FAILURE); // TODO: print error
	if (!(game->config = parse_config(argv[1])))
		return (EXIT_FAILURE); // TODO: print error
	if (!(game->camera = new_camera(game->config)))
		return (EXIT_FAILURE); // TODO: print error
	if (!(game->window = new_window(game->config)))
		return (EXIT_FAILURE); // TODO: print error
	printf_infos(game);
	printf("mouse_hook:%d\n", mlx_mouse_hook(game->window->ptr, &mouse_event, game));
	printf("loop_hook:%d\n", mlx_loop_hook(game->window->ptr, &main_loop, game));
	/*int	x;
	int	y;
	int	color;

	color = 0xFFFFFF;
	y = 0;
	while (y < game->window->height)
	{
		x = 0;
		while (x < game->window->width)
		{
			mlx_pixel_put(game->window->ptr, game->window->win, x++, y, game->config->floor_color);
			color -= 1;
			if (color < 0)
				color = 0xFFFFFF;
		}
		y++;
	}*/
	mlx_loop(game->window->ptr);
	return (EXIT_SUCCESS);
}
