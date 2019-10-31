/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 12:00:15 by ncolomer          #+#    #+#             */
/*   Updated: 2019/10/31 12:38:56 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "config.h"

int
	parse_dimensions(t_config *config, char const *line)
{
	int		i;
	int		tmp;
	t_str	*str;
	t_str	*param;

	i = 0;
	while (line[++i])
		if (line[i] != ' ' && line[i] < '0' && line[i] > '9')
			return (0);
	str = NULL;
	if (!(str = ft_split(line, ' '))
		|| str_length(str) != 3)
		return (str_clear(&str));
	param = str->next;
	tmp = ft_atoi(param->content);
	if (tmp <= 1)
		return (str_clear(&str));
	config->requested_width = tmp;
	param = param->next;
	tmp = ft_atoi(param->content);
	if (tmp <= 1)
		return (str_clear(&str));
	config->requested_height = tmp;
	return (str_clear(&str) | 1);
}

int
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

int
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
	str_to_color(t_str *str)
{
	int	i;
	int	color;
	int	tmp;

	i = 0;
	color = 0;
	while (str)
	{
		tmp = ft_atoi(str->content);
		if (tmp < 0 || tmp > 255)
			return (-1);
		color = color | (tmp << (16 - (i++ * 8)));
		str = str->next;
	}
	return (color);
}

int
	parse_color(t_config *config, char const *line)
{
	int			i;
	unsigned	color;
	t_str		*str[3];

	i = 1;
	while (line[i])
		if (!ft_in_set(line[i++], " ,0123456789"))
			return (0);
	str[0] = NULL;
	str[1] = NULL;
	if (!(str[0] = ft_split(line, ' ')) || str_length(str[0]) != 2
		|| !(str[1] = ft_split(str[0]->next->content, ','))
		|| str_length(str[1]) != 3)
		return (str_clear(&str[0]) && str_clear(&str[1]));
	str[2] = str[1];
	if ((int)((color = str_to_color(str[2]))) < 0)
		return (str_clear(&str[0]) && str_clear(&str[1]));
	i = (line[0] == 'F')
		? (config->floor_color = color)
		: (config->sky_color = color);
	return ((str_clear(&str[0]) && str_clear(&str[1])) | 1);
}
