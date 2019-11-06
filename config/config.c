/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 12:51:45 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/06 20:27:24 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "config.h"

void
	init_config(t_config *config)
{
	config->requested_width = 720;
	config->requested_height = 480;
	config->north_texture_path = NULL;
	config->south_texture_path = NULL;
	config->west_texture_path = NULL;
	config->east_texture_path = NULL;
	config->sprite_texture_path = NULL;
	config->c[0]= 0xFFFFFF;
	config->c[1]= 0xFF0000;
	config->c[2]= 0x00FF00;
	config->c[3]= 0x0000FF;
	config->floor_color = 0xa0764c;
	config->sky_color = 0x33c6e3;
	config->map = NULL;
	config->rows = 0;
	config->columns = 0;
	config->save_arg = 0;
}

int
	clear_config(t_config *config)
{
	if (config->north_texture_path)
		free(config->north_texture_path);
	if (config->south_texture_path)
		free(config->south_texture_path);
	if (config->west_texture_path)
		free(config->west_texture_path);
	if (config->east_texture_path)
		free(config->east_texture_path);
	if (config->sprite_texture_path)
		free(config->sprite_texture_path);
	if (config->map)
		free(config->map);
	return (0);
}

int
	parse_line(t_config *config, char const *line, t_str **map_buffer)
{
	int	length;

	length = ft_strlen(line);
	if (length == 0)
		return (1);
	if (line[0] == 'R')
		return (parse_dimensions(config, line));
	else if ((line[0] == 'N' && line[1] == 'O')
			|| (line[0] == 'S' && line[1] == 'O')
			|| (line[0] == 'W' && line[1] == 'E')
			|| (line[0] == 'E' && line[1] == 'A'))
		return (parse_texture_path(config, line));
	else if (line[0] == 'S')
		return (parse_sprite_texture(config, line));
	else if (line[0] == 'F' || line[0] == 'C')
		return (parse_color(config, line));
	return (!!str_add_back(map_buffer, line));
}

int
	parse_config(t_config *config, char const *conf_path)
{
	int			c_fd;
	char		*line;
	int			r;
	t_str		*map_buffer;

	init_config(config);
	if ((c_fd = open(conf_path, O_RDONLY)) < 0)
		return (0);
	map_buffer = NULL;
	r = 1;
	while (get_next_line(c_fd, &line))
	{
		r = (r && parse_line(config, line, &map_buffer));
		free(line);
	}
	if (r && ft_strlen(line) > 0)
		r = !!str_add_back(&map_buffer, line);
	free(line);
	close(c_fd);
	if ((!r || !parse_map(config, map_buffer)) && !clear_config(config))
		return (str_clear(&map_buffer));
	return (1);
}
