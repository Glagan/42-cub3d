/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 12:51:45 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/09 18:16:25 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

void
	init_config(t_config *config)
{
	int	i;

	config->requested_width = 720;
	config->requested_height = 480;
	i = 0;
	while (i < TEXTURES)
		config->tex_path[i++] = NULL;
	config->c[TEX_NORTH] = 0xFFFFFF;
	config->c[TEX_SOUTH] = 0xCCCCCC;
	config->c[TEX_WEST] = 0xFF44FF;
	config->c[TEX_EAST] = 0x44FF44;
	config->c[TEX_SKY] = 0x33C6E3;
	config->c[TEX_FLOOR] = 0xA0764C;
	config->c[TEX_SKY] = 0x000000;
	config->c[TEX_SPRITE] = 0x00000000;
	config->c[TEX_SPRITE_UP] = 0x00000000;
	config->c[TEX_SPRITE_C] = 0x00000000;
	config->map = NULL;
	config->rows = 0;
	config->columns = 0;
	config->save_arg = 0;
	config->rotate_speed = .11;
	config->move_speed = .11;
	config->fov = .66;
}

int
	clear_config(t_config *config)
{
	int	i;

	i = 0;
	while (i < TEXTURES)
	{
		if (config->tex_path[i])
			free(config->tex_path[i]);
		config->tex_path[i] = NULL;
		i++;
	}
	if (config->map)
		free(config->map);
	config->map = NULL;
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
			|| (line[0] == 'E' && line[1] == 'A')
			|| (line[0] == 'S' && line[1] == 'T')
			|| (line[0] == 'F' && line[1] == 'T')
			|| (line[0] == 'S' && line[1] == ' ')
			|| (line[0] == 'S' && line[1] == 'U')
			|| (line[0] == 'S' && line[1] == 'C'))
		return (parse_texture(config, line));
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
	if (!r || !parse_map(config, map_buffer))
		return (str_clear(&map_buffer));
	str_clear(&map_buffer);
	return (1);
}
