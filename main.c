/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 12:45:06 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/06 11:25:36 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "cub3d.h"

void
	printf_infos(t_game *game)
{
	t_config	*config;
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

	debug_print_camera(game);

	window = game->window;
	printf("#WINDOW" \
		"\nwidth:\t%d" \
		"\nheight:\t%d" \
		"\nptr:\t%p" \
		"\nimage:\t%p" \
		"\nimage_ptr:\t%p" \
		"\nwindow:\t%p\n",
		window->width, window->height,
		window->ptr, window->image.img,
		window->image.ptr, window->win);
}

int
	exit_error(char const *str)
{
	if (str)
		write(STDOUT_FILENO, str, ft_strlen(str));
	return (EXIT_FAILURE);
}

int
	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2) // TODO: look for -save
		return (exit_error("Error:\nNo map specified.\n"));
	if (!(game = new_game()))
		return (exit_error("Error:\nmalloc error.\n"));
	if (!(game->config = parse_config(argv[1])))
		return (exit_error("Error:\nInvalid map.\n"));
	if (!(game->camera = new_camera(game->config)))
		return (exit_error("Error:\nmalloc error.\n"));
	if (!(game->window = new_window(game->config)))
		return (exit_error("Error:\nmlx failed to create window.\n"));
	printf_infos(game);
	mlx_hook(game->window->win, X_EVENT_KEY_PRESS, 0, &key_press, game);
	mlx_hook(game->window->win, X_EVENT_KEY_RELEASE, 0, &key_release, game);
	//mlx_key_hook(game->window->win, &key_event, game);
	mlx_hook(game->window->win, X_EVENT_EXIT, 0, &exit_hook, game);
	mlx_loop_hook(game->window->ptr, &main_loop, game);
	mlx_loop(game->window->ptr);
	return (EXIT_SUCCESS);
}
