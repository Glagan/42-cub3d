/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 00:05:58 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/06 15:11:00 by ncolomer         ###   ########.fr       */
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
		ft_memcpy(window->active_img->ptr +
			(4 * (int)window->size.x * ((int)start->y + i))
			+ ((int)start->x * 4), &color, sizeof(int));
		i++;
	}
	return (1);
}

static void
	restrain_pos(t_pos *pos, t_pos *size)
{
	if (pos->x < 0)
		pos->x = 0;
	if (pos->x > size->x)
		pos->x = size->x;
	if (pos->y < 0)
		pos->y = 0;
	if (pos->y > size->y)
		pos->y = size->y;
}

int
	draw_rectangle_img(t_window *window, t_pos *p1, t_pos *p2, int color)
{
	int	i;
	int	j;

	restrain_pos(p1, &window->size);
	restrain_pos(p2, &window->size);
	i = p1->y;
	while (i < p2->y)
	{
		j = p1->x;
		while (j < p2->x)
		{
			ft_memcpy(window->active_img->ptr +
				(4 * (int)window->size.x * i)
				+ ((int)j * 4), &color, sizeof(int));
			j++;
		}
		i++;
	}
	return (1);
}
