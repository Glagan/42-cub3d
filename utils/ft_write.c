/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 15:22:02 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/10 15:22:48 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int
	ft_write_int(char *buf, int val, int start)
{
	int	length;
	int	tmp;

	length = 1;
	tmp = val;
	while (tmp > 9)
	{
		length++;
		tmp /= 10;
	}
	if (val == 0)
		buf[start++] = '0';
	else
	{
		tmp = length;
		while (val > 0)
		{
			buf[start + --tmp] = "0123456789"[val % 10];
			val /= 10;
		}
		start += length;
	}
	buf[start] = 0;
	return (start);
}

int
	ft_write_str(char *buf, char *str, int start)
{
	int	i;

	i = 0;
	while (str[i])
		buf[start++] = str[i++];
	buf[start] = 0;
	return (start);
}
