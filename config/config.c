/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 12:51:45 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/13 15:37:27 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

void
	init_config(t_config *config)
{
	int	i;

	config->requested_width = 848;
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
	config->map = NULL;
	config->rows = 0;
	config->columns = 0;
	config->save_arg = 0;
	config->rotate_speed = .11;
	config->move_speed = .11;
	config->fov = .66;
	i = 0;
	while (i < C_LAST)
		config->set[i++] = 0;
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

static int
	config_key(char const *line)
{
	if (line[0] == 'R' && line[1] == ' ')
		return (C_R);
	else if (line[0] == 'N' && line[1] == 'O')
		return (C_NO);
	else if (line[0] == 'S' && line[1] == 'O')
		return (C_SO);
	else if (line[0] == 'W' && line[1] == 'E')
		return (C_WE);
	else if (line[0] == 'E' && line[1] == 'A')
		return (C_EA);
	else if (line[0] == 'S' && line[1] == 'T')
		return (C_ST);
	else if (line[0] == 'F' && line[1] == 'T')
		return (C_FT);
	else if (line[0] == 'S' && line[1] == ' ')
		return (C_S);
	else if (line[0] == 'S' && line[1] == 'U')
		return (C_SU);
	else if (line[0] == 'S' && line[1] == 'C')
		return (C_SC);
	else if (line[0] == 'F' && line[1] == ' ')
		return (C_F);
	else if (line[0] == 'C' && line[1] == ' ')
		return (C_C);
	return (C_MAP);
}

int
	parse_line(t_config *config, char const *line, t_str **map_buffer)
{
	static int	empty_in_map = 0;
	static int	content_after = 0;
	int			length;
	int			key;

	length = ft_strlen(line);
	if (length == 0 && config->set[C_MAP])
		empty_in_map = 1;
	if (empty_in_map && content_after)
		return (0);
	if (length == 0)
		return (1);
	key = config_key(line);
	if (key != C_MAP && (config->set[key] || config->set[C_MAP]))
		return (0);
	if (key == C_R)
		return (parse_dimensions(config, line));
	else if (key >= C_NO && key <= C_ST)
		return (parse_texture(config, key, line));
	else if (key == C_F || key == C_C)
		return (parse_color(config, key, line));
	config->set[key] = 1;
	if (empty_in_map)
		content_after = 1;
	return (!!str_add_back(map_buffer, ft_strdup(line)));
}

int
	parse_config(t_config *config, char const *conf_path)
{
	int			c_fd;
	char		*line;
	int			r;
	t_str		*map_buffer;

	if (!ft_endwith(conf_path, ".cub"))
		return (0);
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
		r = !!str_add_back(&map_buffer, ft_strdup(line));
	free(line);
	close(c_fd);
	if (!r || !parse_map(config, map_buffer))
		return (str_clear(&map_buffer));
	str_clear(&map_buffer);
	return (1);
}
