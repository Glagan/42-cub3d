/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 15:30:14 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/06 20:10:57 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void
	load_tex(t_window *window, t_tex *tex, char *path)
{
	if (path)
	{
		tex->path = path;
		tex->tex = mlx_xpm_file_to_image(window->ptr,
			path, &tex->width, &tex->height);
		tex->ptr = mlx_get_data_addr(tex->tex,
			&tex->bpp, &tex->size_line, &tex->endian);
	}
	else
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

/**
 * TODO: Check if texture really loaded
 **/
int
	load_textures(t_game *game)
{
	t_config	*c;
	t_textures	*t;

	c = &game->config;
	t = &game->textures;
	if (c->north_texture_path)
		load_tex(&game->window, &t->north, c->north_texture_path);
	if (c->south_texture_path)
		load_tex(&game->window, &t->south, c->south_texture_path);
	if (c->west_texture_path)
		load_tex(&game->window, &t->west, c->west_texture_path);
	if (c->east_texture_path)
		load_tex(&game->window, &t->east, c->east_texture_path);
	t->sprite.path = NULL;
	t->sprite.tex = NULL;
	t->sprite.ptr = NULL;
	t->t[DIR_NORTH] = (t->north.tex) ? &t->north : NULL;
	t->t[DIR_SOUTH] = (t->south.tex) ? &t->south : NULL;
	t->t[DIR_WEST] = (t->west.tex) ? &t->west : NULL;
	t->t[DIR_EAST] = (t->east.tex) ? &t->east : NULL;
	t->t[DIR_SPRITE] = NULL;
	return (1);
}
