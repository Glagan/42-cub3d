/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 12:51:45 by ncolomer          #+#    #+#             */
/*   Updated: 2019/10/29 16:50:36 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include <stdio.h>

static t_config
	*new_config(void)
{
	t_config	*config;

	config = NULL;
	if (!(config = (t_config*)malloc(sizeof(*config))))
		return (NULL);
	config->requested_width = 1280;
	config->requested_height = 720;
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
	return (config);
}

static int
	parse_dimensions(t_config *config, char const *line)
{
	int	i;
	int	tmp;

	i = 0;
	while (line[++i])
		if (line[i] != ' ' && !(line[i] >= '0' && line[i] <= '9'))
			return (0);
	i = 1;
	while (line[i] && line[i] == ' ')
		i++;
	if (i == 1 || !line[i])
		return (0);
	tmp = 0;
	while (line[i] && line[i] >= '0' && line[i] <= '9')
		tmp = (tmp * 10) + (line[i++] - '0');
	if (tmp <= 0 || !line[i++])
		return (0);
	config->requested_width = tmp;
	tmp = 0;
	while (line[i] && line[i] >= '0' && line[i] <= '9')
		tmp = (tmp * 10) + (line[i++] - '0');
	while (line[i] && line[i] == ' ')
		i++;
	if (tmp <= 0 || line[i])
		return (0);
	config->requested_height = tmp;
	return (1);
}

static int
	parse_texture_path(t_config *config, char const *line)
{
	int		start;
	int		end;
	char	*path;

	if (line[0] == 'N' && line[1] == 'O' && config->north_texture_path)
		free(config->north_texture_path);
	else if (line[0] == 'S' && line[1] == 'O' && config->south_texture_path)
		free(config->south_texture_path);
	else if (line[0] == 'W' && line[1] == 'E' && config->west_texture_path)
		free(config->west_texture_path);
	else if (line[0] == 'E' && line[1] == 'A' && config->east_texture_path)
		free(config->east_texture_path);
	start = 2;
	while (line[start] && line[start] == ' ')
		start++;
	end = ft_strlen(line);
	while (line[end] == ' ')
		end--;
	if (start == 2 || end - start <= 0
		|| !(path = ft_substr(line, start, end - start)))
		return (0);
	if (line[0] == 'N' && line[1] == 'O')
		config->north_texture_path = path;
	else if (line[0] == 'S' && line[1] == 'O')
		config->south_texture_path = path;
	else if (line[0] == 'W' && line[1] == 'E')
		config->west_texture_path = path;
	else if (line[0] == 'E' && line[1] == 'A')
		config->east_texture_path = path;
	return (1);
}

static int
	parse_sprite_texture(t_config *config, char const *line)
{
	int		start;
	int		end;
	char	*path;

	start = 1;
	while (line[start] && line[start] == ' ')
		start++;
	end = ft_strlen(line);
	while (line[end] == ' ')
		end--;
	if (start == 1 || end - start <= 0
		|| !(path = ft_substr(line, start, end - start)))
		return (0);
	config->sprite_texture_path = path;
	return (1);
}

static int
	parse_color(t_config *config, char const *line)
{
	int	i;
	int	rgb;
	int	tmp;
	int	color;

	i = 1;
	while (line[i] && line[i] == ' ')
		i++;
	if (i == 1)
		return (0);
	color = 0;
	rgb = 0;
	while (rgb < 3)
	{
		tmp = 0;
		while (line[i] >= '0' && line[i] <= '9')
			tmp = (tmp * 10) + (line[i++] - '0');
		if (tmp < 0 || tmp > 255
			|| (rgb < 2 && line[i] != ','))
			return (0);
		color += (tmp << (16 - (rgb * 8)));
		if (rgb == 2)
		{
			while (line[i] && line[i] == ' ')
				i++;
			if (line[i])
				return (0);
		}
		i++;
		rgb++;
	}
	if (line[0] == 'F')
		config->floor_color = color;
	else
		config->sky_color = color;
	return (1);
}

t_config
	*parse_config(char const *conf_path)
{
	t_config	*config;
	int			c_fd;
	char		*line;
	int			r;
	int			in_map;
	t_map_buffer	*map_buffer;

	if ((c_fd = open(conf_path, O_RDONLY)) < 0
		|| !(config = new_config()))
		return (NULL);
	map_buffer = NULL;
	line = NULL;
	in_map = 0;
	r = 1;
	while (get_next_line(c_fd, &line))
	{
		if (in_map && ft_strlen(line) == 0)
			r = 0;
		else if (r && in_map)
			r = add_map_line(&map_buffer, line);
		else if (r && ft_strlen(line) > 0)
		{
			if (line[0] == 'R')
				r = parse_dimensions(config, line);
			else if ((line[0] == 'N' && line[1] == 'O')
					|| (line[0] == 'S' && line[1] == 'O')
					|| (line[0] == 'W' && line[1] == 'E')
					|| (line[0] == 'E' && line[1] == 'A'))
				r = parse_texture_path(config, line);
			else if (line[0] == 'S')
				r = parse_sprite_texture(config, line);
			else if (line[0] == 'F' || line[0] == 'C')
				r = parse_color(config, line);
			else
			{
				r = add_map_line(&map_buffer, line);
				in_map = 1;
			}
		}
		free(line);
	}
	if (!in_map)
		return (NULL);
	if (ft_strlen(line) > 0)
		r = add_map_line(&map_buffer, line);
	free(line);
	close(c_fd);
	if (!r || !parse_map(config, &map_buffer))
		return (NULL);
	return (config);
}
