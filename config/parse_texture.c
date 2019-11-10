/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 13:33:50 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/10 18:00:01 by ncolomer         ###   ########.fr       */
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
	texture_index(int key)
{
	if (key == C_NO)
		return (TEX_NORTH);
	else if (key == C_SO)
		return (TEX_SOUTH);
	else if (key == C_WE)
		return (TEX_WEST);
	else if (key == C_EA)
		return (TEX_EAST);
	else if (key == C_ST)
		return (TEX_SKY);
	else if (key == C_FT)
		return (TEX_FLOOR);
	else if (key == C_SU)
		return (TEX_SPRITE_UP);
	else if (key == C_SC)
		return (TEX_SPRITE_C);
	return (TEX_SPRITE);
}

int
	parse_texture(t_config *config, int key, char const *line)
{
	char	*path;
	int		index;

	index = texture_index(key);
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
