/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 13:42:27 by ncolomer          #+#    #+#             */
/*   Updated: 2019/10/29 13:43:20 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char
	*ft_substr(char const *s, unsigned int start, int len)
{
	int		i;
	int		j;
	char	*str;

	str = (char*)malloc(sizeof(*s) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = 0;
	return (str);
}