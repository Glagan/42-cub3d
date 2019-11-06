/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 15:30:14 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/06 18:47:23 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void
	load_tex(t_window *window, t_tex *tex, char *path)
{
	tex->path = path;
	tex->tex = mlx_xpm_file_to_image(window->ptr,
		path, &tex->width, &tex->height);
	tex->ptr = mlx_get_data_addr(tex->tex,
		&tex->bpp, &tex->size_line, &tex->endian);
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
	else
		t->north.tex = NULL;
	if (c->south_texture_path)
		load_tex(&game->window, &t->south, c->south_texture_path);
	else
		t->south.tex = NULL;
	if (c->west_texture_path)
		load_tex(&game->window, &t->west, c->west_texture_path);
	else
		t->west.tex = NULL;
	if (c->east_texture_path)
		load_tex(&game->window, &t->east, c->east_texture_path);
	else
		t->east.tex = NULL;
	t->sprite.tex = NULL;
	return (1);
}
