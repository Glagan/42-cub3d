/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 13:25:07 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/06 21:00:12 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>

# define PTR_CAST(a) (void*)((uintptr_t)(a))

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

t_str			*str_add_back(t_str **str, char const *content);

t_str			*str_last(t_str *str);

int				str_clear(t_str **list);

void			set_pos(t_pos *pos, double x, double y);

void			copy_pos(t_pos *pos, t_pos *org);

#endif
