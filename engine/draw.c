/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 15:45:02 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/03 17:42:53 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "engine.h"

int
	draw_line(t_window *window, t_pos *p1, t_pos *p2, int color)
{
	t_pos	d;
	t_pos	s;
	int		err;
	int		e2;

	//printf("{draw line %lfx1 %lfy1 %lfx1 %lfy1}\n", p1->x, p1->y, p2->x, p2->y);
	d.x = fabs(p2->x - p1->x);
	d.y = fabs(p2->y - p1->y);
	s.x = (p1->x < p2->x) ? 1 : -1;
	s.y = (p1->y < p2->y) ? 1 : -1;
	err = (int)(d.x > d.y ? d.x : -d.y) >> 1;
	while (p1->x != p2->x && p1->y != p2->y)
	{
		mlx_pixel_put(window->ptr, window->win, p1->x, p1->y, color);
		e2 = err;
		if (e2 >- d.x)
		{
			err -= d.y;
			p1->x += s.x;
		}
		if (e2 < d.y)
		{
			err += d.x;
			p1->y += s.y;
		}
	}
	return (1);
}

int
	draw_vertical_line(t_window *window, t_pos *start, int length, int color)
{
	int	i;

	i = 0;
	while (i < length)
	{
		mlx_pixel_put(window->ptr, window->win, start->x, start->y + i, color);
		i++;
	}
	return (1);
}

int
	draw_rectangle(t_window *window, t_pos *p, t_pos *wh, int color)
{
	t_pos	c;

	//printf("{draw rectangle x:%lf y:%lf width:%lf height:%lf}\n", p->x, p->y, wh->x, wh->y);
	c.y = p->y;
	while (c.y < p->y + wh->y)
	{
		c.x = p->x;
		while (c.x < p->x + wh->x)
			mlx_pixel_put(window->ptr, window->win, c.x++, c.y, color);
		c.y++;
	}
	return (1);
}
