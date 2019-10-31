/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 13:24:41 by ncolomer          #+#    #+#             */
/*   Updated: 2019/10/31 13:46:26 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void
	find_start_pos(t_config *config, int *x, int *y, int *angle)
{
	int	stop;

	stop = 0;
	*y = 0;
	while (!stop && *y < config->rows)
	{
		*x = 0;
		while (!stop && *x < config->columns)
		{
			if (ft_in_set(config->map[(*y * config->columns) + *x],
					DIRECTIONS))
			{
				stop = 1;
				break ;
			}
			(*x)++;
		}
		if (!stop)
			(*y)++;
	}
	if (config->map[(*y * config->columns) + *x] == 'N')
		*angle = 270;
	else if (config->map[(*y * config->columns) + *x] == 'E')
		*angle = 0;
	else if (config->map[(*y * config->columns) + *x] == 'S')
		*angle = 90;
	else if (config->map[(*y * config->columns) + *x] == 'W')
		*angle = 180;
}

t_camera
	*new_camera(t_config *config)
{
	int			angle;
	int			x;
	int			y;
	t_camera	*camera;

	if (!(camera = (t_camera*)malloc(sizeof(*camera))))
		return (NULL);
	find_start_pos(config, &x, &y, &angle);
	camera->angle = angle;
	camera->x = x;
	camera->y = y;
	return (camera);
}
