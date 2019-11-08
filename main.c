/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 12:45:06 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/08 16:25:04 by ncolomer         ###   ########.fr       */
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

	config = &game->config;
	printf("#CONFIG" \
		"\nwidth\t\t%d" \
		"\nheight\t\t%d" \
		"\nno_texture\t\"%s\"" \
		"\nso_texture\t\"%s\"" \
		"\nwe_texture\t\"%s\"" \
		"\nea_texture\t\"%s\"" \
		"\nsky_texture\t\"%s\"" \
		"\nfloor_texture\t\"%s\"" \
		"\nsprite_texture\t\"%s\"" \
		"\nnorth_color\t#%08x" \
		"\nsouth_color\t#%08x" \
		"\nwest_color\t#%08x" \
		"\neast_color\t#%08x" \
		"\nsky_color\t#%08x" \
		"\nfloor_color\t#%08x" \
		"\nsprite_color\t#%08x" \
		"\nmap\t\t%dx%d\n",
		config->requested_width, config->requested_height,
		config->tex_path[0], config->tex_path[1],
		config->tex_path[2], config->tex_path[3],
		config->tex_path[4], config->tex_path[5],
		config->tex_path[6],
		config->c[0], config->c[1],
		config->c[2], config->c[3],
		config->c[4], config->c[5],
		config->c[6],
		config->columns, config->rows);
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
	printf("#TEXTURES" \
		"\nnorth:\t%p (%dx%d)" \
		"\nsouth:\t%p (%dx%d)" \
		"\nwest:\t%p (%dx%d)" \
		"\neast:\t%p (%dx%d)" \
		"\nsky:\t%p (%dx%d)" \
		"\nfloor:\t%p (%dx%d)" \
		"\nsprite:\t%p (%dx%d)\n",
		game->tex[0].tex, game->tex[0].width, game->tex[0].height,
		game->tex[1].tex, game->tex[1].width, game->tex[1].height,
		game->tex[2].tex, game->tex[2].width, game->tex[2].height,
		game->tex[3].tex, game->tex[3].width, game->tex[3].height,
		game->tex[4].tex, game->tex[4].width, game->tex[4].height,
		game->tex[5].tex, game->tex[5].width, game->tex[5].height,
		game->tex[6].tex, game->tex[6].width, game->tex[6].height);
	printf("#SPRITES\nfirst: %p\n", game->sprites);
	printf("#OPTIONS\nall: %8x\n", game->options);
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
	if (!find_sprites(&game))
		return (exit_error(&game, "Error:\nfailed to malloc sprites.\n"));
	calculate_camera_x(game.window.size.x, game.camera_x);
	calculate_cos_sin(game.config.rotate_speed, game.cos, game.sin);
	calculate_sf_dist(game.window.size.y, game.sf_dist);
	printf_infos(&game);
	mlx_hook(game.window.win, X_EVENT_KEY_PRESS, 0, &key_press, &game);
	mlx_hook(game.window.win, X_EVENT_KEY_RELEASE, 0, &key_release, &game);
	mlx_hook(game.window.win, X_EVENT_EXIT, 0, &exit_hook, &game);
	mlx_loop_hook(game.window.ptr, &main_loop, &game);
	mlx_loop(game.window.ptr);
	return (EXIT_SUCCESS);
}
