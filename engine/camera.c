/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 13:24:41 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/07 12:08:26 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "engine.h"

static void
	find_start_pos(t_config *config, t_camera *camera)
{
	int	stop;

	stop = 0;
	camera->pos.y = 0;
	while (!stop && camera->pos.y < config->rows)
	{
		camera->pos.x = 0;
		while (!stop && camera->pos.x < config->columns)
		{
			if (ft_in_set(MAP(camera->pos, *config), DIRECTIONS))
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
}

static void
	find_start_angle(t_config *config, t_camera *camera)
{
	if (MAP(camera->pos, *config) == 'N')
	{
		set_pos(&camera->dir, 0, -1);
		set_pos(&camera->plane, .66, 0);
	}
	else if (MAP(camera->pos, *config) == 'E')
	{
		set_pos(&camera->dir, 1, 0);
		set_pos(&camera->plane, 0, .66);
	}
	else if (MAP(camera->pos, *config) == 'S')
	{
		set_pos(&camera->dir, 0, 1);
		set_pos(&camera->plane, -.66, 0);
	}
	else if (MAP(camera->pos, *config) == 'W')
	{
		set_pos(&camera->dir, -1, 0);
		set_pos(&camera->plane, 0, -.66);
	}
	MAP(camera->pos, *config) = '0';
}

void
	init_camera(t_config *config, t_camera *camera)
{
	find_start_pos(config, camera);
	find_start_angle(config, camera);
}

int
	move_camera(t_game *game, int direction)
{
	t_camera	*c;
	t_pos		n_pos;

	c = &game->camera;
	copy_pos(&n_pos, &c->pos);
	n_pos.x += (((direction) ? -1 : 1) * (c->dir.x * .11));
	if (IN_MAP(n_pos, game->config)
		&& MAP(n_pos, game->config) == '0')
		copy_pos(&c->pos, &n_pos);
	copy_pos(&n_pos, &c->pos);
	n_pos.y += (((direction) ? -1 : 1) * (c->dir.y * .11));
	if (IN_MAP(n_pos, game->config)
		&& MAP(n_pos, game->config) == '0')
		copy_pos(&c->pos, &n_pos);
	return (1);
}

int
	rotate_camera(t_game *game, int dir)
{
	t_camera	*c;
	t_pos		old;

	c = &game->camera;
	copy_pos(&old, &c->dir);
	c->dir.x = (c->dir.x * game->cos[dir]) - (c->dir.y * game->sin[dir]);
	c->dir.y = (old.x * game->sin[dir]) + (c->dir.y * game->cos[dir]);
	copy_pos(&old, &c->plane);
	c->plane.x = (c->plane.x * game->cos[dir]) - (c->plane.y * game->sin[dir]);
	c->plane.y = (old.x * game->sin[dir]) + (c->plane.y * game->cos[dir]);
	return (1);
}

void
	debug_print_camera(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->config.rows)
	{
		if (i == 0)
			printf("   0 1 2 3 4 5 6 7 8 9101112131415161718192021222324252627282930\n 0 ");
		else
			printf("%2d ", i);
		j = 0;
		while (j < game->config.columns)
		{
			if (i == (int)game->camera.pos.y
				&& j == (int)game->camera.pos.x)
				printf("  ");
			else
				printf("%c ", MAP_XY(j, i, game->config));
			j++;
		}
		if (i == game->config.rows - 1)
			printf("\n");
		else
			printf("\n");
		i++;
	}
	/*printf("#CAMERA" \
		"\nx:\t%lf" \
		"\ny:\t%lf" \
		"\nplane:\t%lfx %lfy" \
		"\ndir:\t%lfx %lfy\n",
		game->camera.pos.x, game->camera.pos.y,
		game->camera.plane.x, game->camera.plane.y,
		game->camera.dir.x, game->camera.dir.y);*/
}
