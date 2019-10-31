/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 15:45:02 by ncolomer          #+#    #+#             */
/*   Updated: 2019/10/31 17:29:42 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "engine.h"

/**
 * TODO: anti aliased line...
 */
int
	draw_line(t_window *window, t_pos *p1, t_pos *p2, int color)
{
	t_pos	d;
	float	x;
	float	y;
	float	delta_y;
	float	delta_x;

	printf("{draw line x1:%d y1:%d x2:%d y2:%d}\n", p1->x, p1->y, p2->x, p2->y);
	d.x = p2->x - p1->x;
	d.y = p2->y - p1->y;
	x = p1->x;
	y = (float)p1->y;
	delta_y = (p2->x > p1->x) ? ((float)d.y / (float)d.x) : -((float)d.y / (float)d.x);
	delta_y /= 2;
	delta_x = (p2->x > p1->x) ? .5 : -.5;
	while ((int)x != (int)p2->x)
	{
		mlx_pixel_put(window->ptr, window->win, x, y, color);
		y = (y + delta_y);
		x += delta_x;
	}
	return (1);
}

int
	draw_rectangle(t_window *window, t_pos *p, t_pos *wh, int color)
{
	int	x;
	int	y;

	printf("{draw rectangle x:%d y:%d width:%d height:%d}\n", p->x, p->y, wh->x, wh->y);
	y = p->y;
	while (y < p->y + wh->x)
	{
		x = p->x;
		while (x < p->x + wh->y)
			mlx_pixel_put(window->ptr, window->win, x++, y, color);
		y++;
	}
	return (1);
}
