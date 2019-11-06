/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tables.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 00:33:00 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/07 00:37:28 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void
	calculate_camera_x(double width, double r[1080])
{
	int	i;

	i = 0;
	while (i < width)
		r[i++] = ((2. * (double)i) / width) - 1.;
}
