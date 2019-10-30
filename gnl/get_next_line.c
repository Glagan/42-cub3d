/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:19:29 by ncolomer          #+#    #+#             */
/*   Updated: 2019/10/30 12:19:33 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int
	read_file_until_nl(t_str **str, int fd)
{
	char	*buffer;
	int		r;

	if (!(buffer = (char *)malloc(sizeof(*buffer) * (BUFFER_SIZE + 1))))
		return (-1);
	while ((r = read_file(str, buffer, fd)) > 0)
		if (find_nl(NULL, buffer))
			break ;
	free(buffer);
	if (r < 0)
		return (-2);
	return (1);
}

int
	malloc_next_line(t_str **str, char **line)
{
	t_str	*first;
	int		i;
	int		j;
	char	*buffer;

	first = *str;
	j = 0;
	while (*str)
	{
		i = 0;
		while ((*str)->content[i] && (*str)->content[i] != '\n' && ++j)
			i++;
		if ((*str)->content[i] == '\n')
			break ;
		*str = (*str)->next;
	}
	*str = first;
	if (!(buffer = (char *)malloc(sizeof(*buffer) * (j + 1))))
		return (0);
	*line = buffer;
	(*line)[j] = 0;
	return (1);
}

int
	write_next_line(t_str **str, char **line)
{
	int		idx[2];
	int		remaining;
	t_str	*next;

	idx[1] = 0;
	remaining = 0;
	while (*str)
	{
		idx[0] = 0;
		while ((*str)->content[idx[0]] && (*str)->content[idx[0]] != '\n')
			(*line)[idx[1]++] = (*str)->content[idx[0]++];
		if ((*str)->content[idx[0]++] == '\n' && (remaining = 1))
		{
			idx[1] = 0;
			while ((*str)->content[idx[0]])
				(*str)->content[idx[1]++] = (*str)->content[idx[0]++];
			(*str)->content[idx[1]] = 0;
			break ;
		}
		next = (*str)->next;
		free((*str)->content);
		free(*str);
		*str = next;
	}
	return (remaining);
}

static int
	free_all(t_fd **list, int fd, char *buf)
{
	t_fd	*first;
	t_fd	*lt[2];

	first = (list) ? *list : NULL;
	lt[0] = NULL;
	while (list && *list)
	{
		lt[1] = (*list)->next;
		if (fd < 0 || (*list)->fd == fd)
		{
			if (first == (*list))
				first = lt[1];
			str_clear(&(*list)->str);
			free((*list));
			if (lt[0])
				lt[0]->next = lt[1];
		}
		lt[0] = (*list);
		(*list) = lt[1];
	}
	if (list)
		*list = first;
	if (buf)
		free(buf);
	return (0);
}

int
	get_next_line(int fd, char **line)
{
	static t_fd	*list = NULL;
	t_fd		*current;
	int			read_rem;
	char		*buffer;
	int			r;

	if (!(current = find_fd(&list, fd, &read_rem)))
		return (free_all(&list, -1, NULL) | -1);
	if ((buffer = NULL) || (!read_rem && current->str))
		read_rem = !find_nl(current->str, NULL);
	if (read_rem && (r = read_file_until_nl(&current->str, fd)) < 0)
		return (free_all(&list, (r == -1) ? -1 : fd, NULL) | -1);
	if (!malloc_next_line(&current->str, line))
		return (free_all(&list, -1, NULL) | -1);
	if (!(read_rem = write_next_line(&current->str, line)))
	{
		if (!(buffer = (char*)malloc(sizeof(*buffer) * (BUFFER_SIZE + 1))))
			return (free_all(&list, -1, NULL));
		r = read_file(&current->str, buffer, fd);
		if (free_all(NULL, -1, buffer) || r < 0)
			return (free_all(&list, fd, NULL) | -1);
	}
	if (r > 0 || read_rem)
		return (1);
	return (free_all(&list, fd, NULL));
}
