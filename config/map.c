/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 15:24:13 by ncolomer          #+#    #+#             */
/*   Updated: 2019/10/29 16:55:16 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "config.h"

int
	add_map_line(t_map_buffer **map_buffer, char const *line)
{
	t_map_buffer	*first;
	t_map_buffer	*new;

	if (!(new = (t_map_buffer*)malloc(sizeof(*new))))
		return (0);
	new->line = NULL;
	new->next = NULL;
	if (!*map_buffer)
		*map_buffer = new;
	else
	{
		first = *map_buffer;
		while ((*map_buffer)->next)
			*map_buffer = (*map_buffer)->next;
		(*map_buffer)->next = new;
		*map_buffer = first;
	}
	if (!(new->line = ft_strdup(line)))
		return (0);
	return (1);
}

int
	check_top_bottom_borders(t_map_buffer **map_buffer)
{
	int				i[2];
	int				j[2];
	t_map_buffer	*first;

	first = *map_buffer;
	if (!*map_buffer)
		return (0);
	i[0] = 0;
	i[1] = 0;
	while ((*map_buffer)->line[i[0]])
	{
		if ((*map_buffer)->line[i[0]] == '1')
			i[1]++;
		else if ((*map_buffer)->line[i[0]] != ' ')
			return (0);
		i[0]++;
	}
	while ((*map_buffer)->next)
		*map_buffer = (*map_buffer)->next;
	j[0] = 0;
	j[1] = 0;
	while ((*map_buffer)->line[j[0]])
	{
		if ((*map_buffer)->line[j[0]] == '1')
			j[1]++;
		else if ((*map_buffer)->line[j[0]] != ' ')
			return (0); // todo: set back first
		j[0]++;
	}
	*map_buffer = first;
	if (i[1] == j[1])
		return (i[1]);
	return (0);
}

int
	check_left_right_borders(t_map_buffer **map_buffer)
{
	int				i;
	int				j[2];
	t_map_buffer	*first;

	first = *map_buffer;
	if (!*map_buffer)
		return (0);
	i = 0;
	while (*map_buffer)
	{
		j[0] = 0;
		while ((*map_buffer)->line[j[0]] == ' ')
			j[0]++;
		j[1] = ft_strlen((*map_buffer)->line) - 1;
		while (j[1] > 0 && j[1] == ' ')
			j[1]--;
		if (j[1] <= 1
			|| (*map_buffer)->line[j[0]] != '1'
			|| (*map_buffer)->line[j[1]] != '1')
			return (0); // todo: set back first
		*map_buffer = (*map_buffer)->next;
		i++;
	}
	*map_buffer = first;
	return (i);
}

int
	parse_map(t_config *config, t_map_buffer **map_buffer)
{
	int				i;
	int 			j[2];
	int				has_camera;
	int				*map;
	t_map_buffer	*tmp;

	if ((config->columns = check_top_bottom_borders(map_buffer)) <= 2
		|| (config->rows = check_left_right_borders(map_buffer)) <= 2)
		return (0);
	if (!(map = (int*)malloc(sizeof(*map) * (config->rows * config->columns))))
		return (0);
	i = 0;
	while (*map_buffer)
	{
		j[0] = 0;
		j[1] = 0;
		while ((*map_buffer)->line[j[0]])
		{
			while ((*map_buffer)->line[j[0]] == ' ')
				j[0]++;
			map[(i * config->columns) + j[1]++] = (*map_buffer)->line[j[0]];
			if ((*map_buffer)->line[j[0]] == 'N' || (*map_buffer)->line[j[0]] == 'S'
				|| (*map_buffer)->line[j[0]] == 'E'
				|| (*map_buffer)->line[j[0]] == 'W')
				has_camera = 1;
			j[0]++;
		}
		tmp = (*map_buffer)->next;
		free((*map_buffer)->line);
		free(*map_buffer);
		*map_buffer = tmp;
		i++;
	}
	config->map = map;
	if (!has_camera)
		return (0);
	return (1);
}
