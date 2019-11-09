/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 15:24:13 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/09 13:28:13 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

int
	copy_map(t_config *config, t_str *map_buffer, int *map)
{
	int		i;
	int		j;
	int		line;
	int		has_camera;

	i = 0;
	has_camera = 0;
	while (map_buffer)
	{
		j = 0;
		line = 0;
		while (map_buffer->content[j])
		{
			while (map_buffer->content[j] == ' ')
				j++;
			map[(i * config->columns) + line++] = map_buffer->content[j];
			if (ft_in_set(map_buffer->content[j], DIRECTIONS))
				has_camera++;
			j++;
		}
		map_buffer = map_buffer->next;
		i++;
	}
	return (has_camera);
}

int
	parse_map(t_config *config, t_str *map_buffer)
{
	int		*map;

	map = NULL;
	if ((config->columns = check_top_bottom_borders(map_buffer)) <= 2
		|| (config->rows = check_left_right_borders(map_buffer)) <= 2
		|| !check_valid(config, map_buffer))
		return (0);
	if (!(map = (int*)malloc(sizeof(*map) * (config->rows * config->columns))))
		return (0);
	if (copy_map(config, map_buffer, map) != 1)
		return (0);
	config->map = map;
	return (1);
}
