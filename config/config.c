/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 12:51:45 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/03 17:29:08 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include <stdio.h>

static t_config
	*new_config(void)
{
	t_config	*config;

	if (!(config = (t_config*)malloc(sizeof(*config))))
		return (NULL);
	config->requested_width = 720;
	config->requested_height = 480;
	config->north_texture_path = NULL;
	config->south_texture_path = NULL;
	config->west_texture_path = NULL;
	config->east_texture_path = NULL;
	config->sprite_texture_path = NULL;
	config->floor_color = 0xa0764c;
	config->sky_color = 0x33c6e3;
	config->map = NULL;
	config->rows = 0;
	config->columns = 0;
	config->save_arg = 0;
	config->fov = 1.0471975512;
	return (config);
}

int
	clear_config(t_config **config)
{
	if ((*config)->north_texture_path)
		free((*config)->north_texture_path);
	if ((*config)->south_texture_path)
		free((*config)->south_texture_path);
	if ((*config)->west_texture_path)
		free((*config)->west_texture_path);
	if ((*config)->east_texture_path)
		free((*config)->east_texture_path);
	if ((*config)->sprite_texture_path)
		free((*config)->sprite_texture_path);
	if ((*config)->map)
		free((*config)->map);
	free(*config);
	*config = NULL;
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

// TODO: Fix possible leaks everywhere

t_config
	*parse_config(char const *conf_path)
{
	t_config	*config;
	int			c_fd;
	char		*line;
	int			r;
	t_str		*map_buffer;

	if ((c_fd = open(conf_path, O_RDONLY)) < 0
		|| !(config = new_config()))
		return (NULL);
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
	if ((!r || !parse_map(config, map_buffer)) && !clear_config(&config))
		return (PTR_CAST(str_clear(&map_buffer)));
	return (config);
}
