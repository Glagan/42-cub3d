/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:19:57 by ncolomer          #+#    #+#             */
/*   Updated: 2019/10/29 13:09:38 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

typedef struct	s_str
{
	char			*content;
	struct s_str	*next;
}				t_str;

typedef struct	s_fd
{
	int			fd;
	t_str		*str;
	struct s_fd	*next;
}				t_fd;

int				get_next_line(int fd, char **line);

char			*ft_strdup(char const *s1);

t_fd			*find_fd(t_fd **list, int fd, int *new);

int				find_nl(t_str *str, char *sim_str);

int				read_file(t_str **str, char *buffer, int fd);

int				lst_clear(t_str **list);

#endif
