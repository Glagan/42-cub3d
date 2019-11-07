/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 15:30:14 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/07 12:34:02 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "engine.h"

static void
	load_tex(t_window *window, t_tex *tex, char *path)
{
	int	set_null;

	set_null = !path;
	if (!set_null)
	{
		tex->path = path;
		if ((tex->tex = mlx_xpm_file_to_image(window->ptr,
			path, &tex->width, &tex->height)))
			tex->ptr = mlx_get_data_addr(tex->tex,
				&tex->bpp, &tex->size_line, &tex->endian);
		else
			set_null = 1;
	}
	if (set_null)
	{
		tex->path = NULL;
		tex->tex = NULL;
		tex->ptr = NULL;
		tex->endian = 0;
		tex->bpp = 0;
		tex->size_line = 0;
		tex->width = 0;
		tex->height = 0;
	}
}

int
	load_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		load_tex(&game->window, &game->tex[i], game->config.tex_path[i]);
		i++;
	}
	return (1);
}
