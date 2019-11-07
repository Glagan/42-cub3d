/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tables.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 00:33:00 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/07 17:42:29 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void
	calculate_camera_x(double width, double r[1080])
{
	int	i;

	i = 0;
	while (i < width)
	{
		r[i] = ((2. * (double)i) / width) - 1.;
		i++;
	}
}

void
	calculate_cos_sin(double rotate_speed, double _cos[2], double _sin[2])
{
	_cos[0] = cos(-rotate_speed);
	_cos[1] = cos(rotate_speed);
	_sin[0] = sin(-rotate_speed);
	_sin[1] = sin(rotate_speed);
}
