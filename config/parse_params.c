/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 12:00:15 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/07 12:18:34 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static char
	*path_from_line(int start, char const *line)
{
	int		start_def;
	int		end;
	char	*path;

	start_def = start;
	if (!line)
		return (NULL);
	while (line[start] && line[start] == ' ')
		start++;
	end = ft_strlen(line);
	while (line[end] == ' ')
		end--;
	if (start == start_def || end - start <= 0
		|| !(path = ft_substr(line, start, end - start)))
		return (NULL);
	return (path);
}

int
	parse_texture(t_config *config, char const *line)
{
	char	*path;
	int		index;
	char	c1;
	char	c2;

	c1 = line[0];
	c2 = line[1];
	index = TEX_SPRITE;
	if (c1 == 'N' && c2 == 'O')
		index = TEX_NORTH;
	else if (c1 == 'S' && c2 == 'O')
		index = TEX_SOUTH;
	else if (c1 == 'W' && c2 == 'E')
		index = TEX_WEST;
	else if (c1 == 'E' && c2 == 'A')
		index = TEX_EAST;
	else if (c1 == 'S' && c2 == 'T')
		index = TEX_SKY;
	else if (c1 == 'F' && c2 == 'T')
		index = TEX_FLOOR;
	if (config->tex_path[index])
	{
		free(config->tex_path[index]);
		config->tex_path[index] = NULL;
	}
	if (!(path = path_from_line((index == TEX_SPRITE) ? 1 : 2, line)))
		return (0);
	config->tex_path[index] = path;
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
	config->c[(line[0] == 'F') ? TEX_FLOOR : TEX_SKY] = color;
	return ((str_clear(&str[0]) && str_clear(&str[1])) | 1);
}
