/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 13:33:50 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/09 17:06:01 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

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

static int
	texture_index(char c1, char c2)
{
	if (c1 == 'N' && c2 == 'O')
		return (TEX_NORTH);
	else if (c1 == 'S' && c2 == 'O')
		return (TEX_SOUTH);
	else if (c1 == 'W' && c2 == 'E')
		return (TEX_WEST);
	else if (c1 == 'E' && c2 == 'A')
		return (TEX_EAST);
	else if (c1 == 'S' && c2 == 'T')
		return (TEX_SKY);
	else if (c1 == 'F' && c2 == 'T')
		return (TEX_FLOOR);
	else if (c1 == 'S' && c2 == 'U')
		return (TEX_SPRITE_UP);
	return (TEX_SPRITE);
}

int
	parse_texture(t_config *config, char const *line)
{
	char	*path;
	int		index;

	index = texture_index(line[0], line[1]);
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
