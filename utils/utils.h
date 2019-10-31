/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 13:25:07 by ncolomer          #+#    #+#             */
/*   Updated: 2019/10/31 11:51:23 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>

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

int				str_length(t_str *str);

t_str			*str_add_back(t_str **str, char const *content);

t_str			*str_last(t_str *str);

int				str_clear(t_str **list);

#endif
