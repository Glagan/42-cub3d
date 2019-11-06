/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 15:30:14 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/06 15:50:18 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

/**
 * TODO: Check if texture really loaded
 **/
int
	load_textures(t_game *game)
{
	t_config	*c;
	t_textures	*t;

	c = game->config;
	t = &game->textures;
	if (c->north_texture_path)
		t->no_tex = mlx_xpm_file_to_image(game->window->ptr,
			c->north_texture_path, &t->no_width, &t->no_height);
	else
		t->no_tex = NULL;
	if (c->south_texture_path)
		t->so_tex = mlx_xpm_file_to_image(game->window->ptr,
			c->south_texture_path, &t->so_width, &t->so_height);
	else
		t->so_tex = NULL;
	if (c->west_texture_path)
		t->we_tex = mlx_xpm_file_to_image(game->window->ptr,
			c->west_texture_path, &t->we_width, &t->we_height);
	else
		t->we_tex = NULL;
	if (c->east_texture_path)
		t->ea_tex = mlx_xpm_file_to_image(game->window->ptr,
			c->east_texture_path, &t->ea_width, &t->ea_height);
	else
		t->ea_tex = NULL;
	t->sprite_tex = NULL;
	return (1);
}
