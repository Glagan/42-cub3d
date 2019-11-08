/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tables.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 00:33:00 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/08 18:37:56 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void
	calculate_camera_x(double width, double *r)
{
	int	i;

	i = 0;
	while (i < width)
	{
		r[i] = ((2. * (double)i) / width) - 1.;
		i++;
	}
}

static void
	calculate_cos_sin(double rotate_speed, double *cos_r, double *sin_r)
{
	cos_r[0] = cos(-rotate_speed);
	cos_r[1] = cos(rotate_speed);
	sin_r[0] = sin(-rotate_speed);
	sin_r[1] = sin(rotate_speed);
}

static void
	calculate_sf_dist(double height, double *r)
{
	int	i;

	i = 0;
	while (i < height)
	{
		r[i] = (height / (2. * (double)i - height));
		i++;
	}
}

void
	make_tables(t_game *game)
{
	calculate_camera_x(game->window.size.x, game->camera_x);
	calculate_cos_sin(game->config.rotate_speed, game->cos, game->sin);
	calculate_sf_dist(game->window.size.y, game->sf_dist);
}
