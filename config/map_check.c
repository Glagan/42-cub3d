/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 11:47:56 by ncolomer          #+#    #+#             */
/*   Updated: 2019/10/31 11:48:27 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

int
	count_check_columns(char const *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '1')
			j++;
		else if (line[i] != ' ')
			return (0);
		i++;
	}
	return (j);
}

int
	check_top_bottom_borders(t_str *map_buffer)
{
	int		first_line;
	int		last_line;
	t_str	*last;

	if (!map_buffer)
		return (0);
	first_line = count_check_columns(map_buffer->content);
	last = str_last(map_buffer);
	if (last)
		last_line = count_check_columns(last->content);
	else
		last_line = 0;
	if (first_line == last_line)
		return (first_line);
	return (0);
}

int
	check_left_right_borders(t_str *map_buffer)
{
	int				i;
	int				first;
	int				last;

	if (!map_buffer)
		return (0);
	i = 0;
	while (map_buffer)
	{
		first = 0;
		while (map_buffer->content[first] == ' ')
			first++;
		last = ft_strlen(map_buffer->content) - 1;
		while (last > 0 && last == ' ')
			last--;
		if (last <= 1
			|| map_buffer->content[first] != '1'
			|| map_buffer->content[last] != '1')
			return (0);
		map_buffer = map_buffer->next;
		i++;
	}
	return (i);
}

int
	check_valid(t_config *config, t_str *map_buffer)
{
	int	i;
	int	col;

	while (map_buffer)
	{
		i = 0;
		col = 0;
		while (map_buffer->content[i])
		{
			if (!ft_in_set(map_buffer->content[i], VALID_MAP_CHARACTERS))
				return (0);
			if (map_buffer->content[i++] != ' ')
				col++;
		}
		if (col != config->columns)
			return (0);
		map_buffer = (map_buffer)->next;
	}
	return (1);
}
