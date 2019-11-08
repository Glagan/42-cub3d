/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tables.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 00:33:00 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/08 14:56:49 by ncolomer         ###   ########.fr       */
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
	calculate_cos_sin(double rotate_speed, double cos_r[2], double sin_r[2])
{
	cos_r[0] = cos(-rotate_speed);
	cos_r[1] = cos(rotate_speed);
	sin_r[0] = sin(-rotate_speed);
	sin_r[1] = sin(rotate_speed);
}
