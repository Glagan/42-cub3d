/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 13:25:07 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/13 14:25:37 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>

# define PTR_CAST(a)	(void*)((uintptr_t)(a))
# define MAX(a, b)		((a > b) ? a : b)

typedef struct	s_pos
{
	double	x;
	double	y;
}				t_pos;

typedef struct	s_str
{
	char			*content;
	struct s_str	*next;
}				t_str;

int				ft_strlen(char const *str);

int				ft_in_set(char c, char const *set);

char			*ft_substr(char const *s, int start, int len);

char			*ft_strdup(char const *s1);

int				ft_atoi(char const *str);

t_str			*ft_split(char const *org, char sep);

char			*ft_itoa(int n);

int				str_length(t_str *str);

t_str			*str_add_back(t_str **str, char *content);

t_str			*str_last(t_str *str);

int				str_clear(t_str **list);

void			set_pos(t_pos *pos, double x, double y);

void			copy_pos(t_pos *pos, t_pos *org);

void			*ft_memmove(void *dst, const void *src, unsigned long len);

int				ft_strcmp(const char *s1, const char *s2);

int				ft_write_int(char *buf, int val, int start);

int				ft_write_str(char *buf, char *str, int start);

int				ft_endwith(char const *str, char const *end);

#endif
