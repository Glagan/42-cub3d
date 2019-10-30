/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 12:22:09 by ncolomer          #+#    #+#             */
/*   Updated: 2019/10/30 12:22:17 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char
	*ft_strdup(char const *s1)
{
	char	*str;
	size_t	i;

	if (!s1)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		i++;
	}
	str = (char*)malloc(sizeof(*str) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = 0;
	return (str);
}
