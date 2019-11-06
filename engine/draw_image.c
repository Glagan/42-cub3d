/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 00:05:58 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/06 13:45:50 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int
	draw_vertical_line_img(t_window *window, t_pos *start,
							int length, int color)
{
	int	i;

	if (start->x < 0)
		start->x = 0;
	if (start->y < 0)
		start->y = 0;
	if (start->x > window->size.x)
		start->x = window->size.x;
	if (start->y + length > window->size.y)
		length = window->size.y - start->y;
	i = 0;
	while (i < length)
	{
		ft_memcpy(window->image.ptr +
			(4 * (int)window->size.x * ((int)start->y + i))
			+ ((int)start->x * 4), &color, sizeof(int));
		i++;
	}
	return (1);
}
