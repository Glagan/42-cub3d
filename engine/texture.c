/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 15:30:14 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/09 17:06:38 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "engine.h"

static int
	load_tex(t_window *window, t_tex *tex, char *path)
{
	if (path)
	{
		tex->path = path;
		if ((tex->tex = mlx_xpm_file_to_image(window->ptr,
			path, &tex->width, &tex->height)))
			tex->ptr = mlx_get_data_addr(tex->tex,
				&tex->bpp, &tex->size_line, &tex->endian);
		else
			return (0);
	}
	return (1);
}

void
	clear_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < TEXTURES)
	{
		if (game->tex[i].tex)
			mlx_destroy_image(game->window.ptr, game->tex[i].tex);
		game->tex[i].tex = NULL;
		game->tex[i].ptr = NULL;
		i++;
	}
}

int
	load_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < TEXTURES)
	{
		if (!load_tex(&game->window, &game->tex[i], game->config.tex_path[i]))
			return (0);
		i++;
	}
	return (1);
}
