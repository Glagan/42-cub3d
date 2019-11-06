/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 12:45:06 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/06 20:26:51 by ncolomer         ###   ########.fr       */
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
	t_textures	*tex;

	config = &game->config;
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

	window = &game->window;
	printf("#WINDOW" \
		"\nwidth:\t%lf" \
		"\nheight:\t%lf" \
		"\nptr:\t%p" \
		"\nimage:\t%p" \
		"\nimage_ptr:\t%p" \
		"\nwindow:\t%p\n",
		window->size.x, window->size.y,
		window->ptr, window->screen.img,
		window->screen.ptr, window->win);

	tex = &game->textures;
	printf("#TEXTURES" \
		"\nnorth:\t%p (%dx%d)" \
		"\nsouth:\t%p (%dx%d)" \
		"\nwest:\t%p (%dx%d)" \
		"\neast:\t%p (%dx%d)\n",
		tex->north.tex, tex->north.width, tex->north.height,
		tex->south.tex, tex->south.width, tex->south.height,
		tex->west.tex, tex->west.width, tex->west.height,
		tex->east.tex, tex->east.width, tex->east.height);
}

int
	exit_error(t_game *game, char const *str)
{
	clear_config(&game->config);
	destroy_window(&game->window);
	if (str)
		write(STDOUT_FILENO, str, ft_strlen(str));
	return (EXIT_FAILURE);
}

int
	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2) // TODO: look for -save
		return (exit_error(&game, "Error:\nno map specified.\n"));
	init_game(&game);
	if (!parse_config(&game.config, argv[1]))
		return (exit_error(&game, "Error:\ninvalid map.\n"));
	init_camera(&game.config, &game.camera);
	if (!init_window(&game.window, &game.config))
		return (exit_error(&game, "Error:\nmlx failed to create window.\n"));
	if (!load_textures(&game))
		return (exit_error(&game, "Error:\nfailed to load texture(s).\n"));
	//printf_infos(&game);
	mlx_hook(game.window.win, X_EVENT_KEY_PRESS, 0, &key_press, &game);
	mlx_hook(game.window.win, X_EVENT_KEY_RELEASE, 0, &key_release, &game);
	mlx_hook(game.window.win, X_EVENT_EXIT, 0, &exit_hook, &game);
	mlx_loop_hook(game.window.ptr, &main_loop, &game);
	mlx_loop(game.window.ptr);
	return (EXIT_SUCCESS);
}
