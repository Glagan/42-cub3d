/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 12:45:06 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/09 17:37:35 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d.h"

int
	exit_error(t_game *game, char const *str)
{
	if (str)
		write(STDOUT_FILENO, str, ft_strlen(str));
	exit_game(game, EXIT_FAILURE);
	return (EXIT_FAILURE);
}

int
	main(int argc, char **argv)
{
	t_game	game;
	int		save_opt;

	save_opt = (argc >= 2 && !ft_strcmp(argv[1], "-save"));
	if (argc < (2 + save_opt))
		return (exit_error(&game, "Error:\nno map specified.\n"));
	init_game(&game, save_opt);
	if (!parse_config(&game.config, argv[1 + save_opt]))
		return (exit_error(&game, "Error:\ninvalid map.\n"));
	if (!finish_init(&game))
		return (EXIT_FAILURE);
	if (game.options & FLAG_SAVE)
		return (screenshot(&game));
	mlx_hook(game.window.win, X_EVENT_KEY_PRESS, 0, &key_press, &game);
	mlx_hook(game.window.win, X_EVENT_KEY_RELEASE, 0, &key_release, &game);
	mlx_hook(game.window.win, X_EVENT_EXIT, 0, &exit_hook, &game);
	mlx_loop_hook(game.window.ptr, &main_loop, &game);
	mlx_loop(game.window.ptr);
	return (EXIT_SUCCESS);
}
