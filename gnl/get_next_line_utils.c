/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:00:46 by ncolomer          #+#    #+#             */
/*   Updated: 2019/10/30 12:22:24 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_fd
	*find_fd(t_fd **list, int fd, int *new)
{
	t_fd	*ret;
	t_fd	*first;

	ret = NULL;
	first = *list;
	*new = 0;
	while (*list && !ret)
	{
		if ((*list)->fd == fd)
			ret = *list;
		*list = (*list)->next;
	}
	*list = first;
	if (!ret)
	{
		if (!(ret = (t_fd *)malloc(sizeof(*ret))))
			return (NULL);
		ret->fd = fd;
		ret->next = *list;
		ret->str = NULL;
		*list = ret;
		*new = 1;
	}
	return (ret);
}

int
	find_nl(t_str *str, char *sim_str)
{
	int	i;

	if (!str)
	{
		i = 0;
		while (sim_str[i] && sim_str[i] != '\n')
			i++;
		if (sim_str[i] == '\n')
			return (1);
	}
	else
	{
		while (str)
		{
			i = 0;
			while (str->content[i]
				&& str->content[i] != '\n')
				i++;
			if (str->content[i] == '\n')
				return (1);
			str = str->next;
		}
	}
	return (0);
}

int
	read_file(t_str **str, char *buffer, int fd)
{
	int		r;
	t_str	*new;
	t_str	*first;

	if ((r = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[r] = 0;
		if (!(new = (t_str*)malloc(sizeof(*new)))
			|| !(new->content = ft_strdup(buffer)))
			return (-2);
		new->next = NULL;
		if (!*str)
			*str = new;
		else
		{
			first = *str;
			while ((*str)->next)
				(*str) = (*str)->next;
			(*str)->next = new;
			*str = first;
		}
		return (1);
	}
	return ((r < 0) ? -1 : 0);
}

int
	lst_clear(t_str **list)
{
	t_str	*tmp;

	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->content);
		free(*list);
		(*list) = tmp;
	}
	*list = NULL;
	return (0);
}
