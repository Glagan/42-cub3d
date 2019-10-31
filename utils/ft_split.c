/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 10:43:10 by ncolomer          #+#    #+#             */
/*   Updated: 2019/10/31 12:21:04 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_str
	*ft_split(char const *org, char sep)
{
	int		i;
	int		start;
	t_str	*str;

	start = 0;
	i = 0;
	str = NULL;
	while (org[i])
	{
		if (org[i] == sep)
		{
			if (i - start > 0
				&& !str_add_back(&str, ft_substr(org, start, i - start)))
				return (PTR_CAST(str_clear(&str)));
			start = ++i;
		}
		else
			i++;
	}
	if (i - start > 0
		&& !str_add_back(&str, ft_substr(org, start, i - start)))
		return (PTR_CAST(str_clear(&str)));
	return (str);
}
