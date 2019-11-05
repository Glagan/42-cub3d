/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 00:05:58 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/06 00:05:58 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int
	draw_vertical_line_img(t_window *window, t_pos *start,
							int length, int color)
{
	int	i;

	i = 0;
	while (i < length)
	{
		*(window->image->ptr +
			(4 * window->size.x * (start.y + i)) + (start->x * 4))
		= color | 0xFFFFFF;
		i++;
	}
	return (1);
}
