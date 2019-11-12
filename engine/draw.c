/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 00:05:58 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/12 17:14:01 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void
	draw_pixel(t_window *w, t_pos *pos, int color)
{
	if (pos->x >= 0 && pos->x < w->size.x
		&& pos->y >= 0 && pos->y < w->size.y)
		*(int*)(w->screen.ptr
			+ (4 * (int)w->size.x * (int)pos->y)
			+ ((int)pos->x * 4)) = color;
}

int
	draw_vertical_line(t_window *window, t_pos *start,
							int length, int color)
{
	int		i;
	int		j;
	t_pos	pos;
	int		limit;

	if (start->x < 0 || start->x > window->size.x)
		return (1);
	pos.x = start->x;
	limit = (int)window->size.y;
	i = 0;
	while (i < length && (j = start->y + i) < limit)
	{
		pos.y = j;
		draw_pixel(window, &pos, color);
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
		pos->x = size->x - 1;
	if (pos->y < 0)
		pos->y = 0;
	if (pos->y > size->y)
		pos->y = size->y - 1;
}

int
	draw_rectangle(t_window *window, t_pos *p1, t_pos *p2, int color)
{
	int		i;
	int		j;
	t_pos	pos;

	restrain_pos(p1, &window->size);
	restrain_pos(p2, &window->size);
	i = p1->y;
	while (i < p2->y)
	{
		pos.y = i;
		j = p1->x;
		while (j < p2->x)
		{
			pos.x = j++;
			draw_pixel(window, &pos, color);
		}
		i++;
	}
	return (1);
}
