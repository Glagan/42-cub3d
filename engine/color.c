/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 12:33:48 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/09 14:07:13 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int
	shade_color(int color, double divide)
{
	if (divide <= 1.)
		return (color);
	return (((int)(((0xFF0000 & color) >> 16) / divide) << 16)
		+ ((int)(((0x00FF00 & color) >> 8) / divide) << 8)
		+ ((int)((0x0000FF & color) / divide)));
}

int
	distance_shade(int options, int color, double distance)
{
	if (options & FLAG_SHADOWS)
		return (shade_color(color, distance / 1.5));
	return (color);
}

/*
** TODO: removed limit check, be careful
*/

int
	get_tex_color(t_tex *tex, t_pos *pos)
{
	return (*(int*)(tex->ptr
		+ (4 * tex->width * (int)pos->y)
		+ (4 * (int)pos->x)));
}
