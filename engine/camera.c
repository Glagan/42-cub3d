/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 13:24:41 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/02 19:59:26 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "engine.h"

static void
	find_start_pos_angle(t_config *config, t_camera *camera)
{
	int	stop;

	stop = 0;
	camera->pos.y = 0;
	while (!stop && camera->pos.y < config->rows)
	{
		camera->pos.x = 0;
		while (!stop && camera->pos.x < config->columns)
		{
			if (ft_in_set(MAP(camera->pos, config), DIRECTIONS))
			{
				stop = 1;
				break ;
			}
			(camera->pos.x)++;
		}
		if (!stop)
			(camera->pos.y)++;
	}
	camera->pos.x += .5;
	camera->pos.y += .5;
	if (MAP(camera->pos, config) == 'N')
		camera->angle = M_PI_2;
	else if (MAP(camera->pos, config) == 'E')
		camera->angle = 0.;
	else if (MAP(camera->pos, config) == 'S')
		camera->angle = M_3_PI_2;
	else if (MAP(camera->pos, config) == 'W')
		camera->angle = M_PI;
	MAP(camera->pos, config) = '0';
}

t_camera
	*new_camera(t_config *config)
{
	t_camera	*camera;

	if (!(camera = (t_camera*)malloc(sizeof(*camera))))
		return (NULL);
	find_start_pos_angle(config, camera);
	return (camera);
}

int
	move_camera(t_game *game, double angle)
{
	t_pos		n_pos;
	t_camera	*camera;

	camera = game->camera;
	copy_pos(&n_pos, &camera->pos);
	n_pos.x += (cos(M_2_M_PI - angle) * .2);
	n_pos.y += (sin(M_2_M_PI - angle) * .2);
	printf("{trying to move to x%lfy%lf}\n", n_pos.x, n_pos.y);
	if (n_pos.x < game->config->columns && n_pos.y < game->config->rows
		&& MAP(n_pos, game->config) == '0')
	{
		printf("{moved to x%lfy%lf}\n", n_pos.x, n_pos.y);
		copy_pos(&camera->pos, &n_pos);
		return (1);
	}
	return (0);
}

void
	debug_print_camera(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->config->rows)
	{
		j = 0;
		while (j < game->config->columns)
		{
			if (i == (int)game->camera->pos.y && j == (int)game->camera->pos.x)
				printf("  ");
			else
				printf("%c ", MAP_XY(j, i, game->config));
			j++;
		}
		if (i == game->config->rows - 1)
			printf("\n");
		else
			printf("\n");
		i++;
	}
	printf("#CAMERA" \
		"\nx:\t%lf" \
		"\ny:\t%lf" \
		"\nangle:\t%lf (radians)\n",
		game->camera->pos.x, game->camera->pos.y, game->camera->angle);
}
